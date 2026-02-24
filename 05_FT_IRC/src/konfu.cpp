#include <arpa/inet.h>
#include <cerrno>
#include <csignal>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <ctime>

using std::cerr;
using std::endl;
using std::string;
using std::vector;

typedef struct s_buf {
  char buf[1024];
  char *start;
  unsigned int buffer_size;
} t_buf;

ssize_t gnl_read_buf(int fd, t_buf *rb) {
  ssize_t nb_read;

  if (fd < 0 || rb == NULL)
    return (-1);
  nb_read = recv(fd, rb->buf, rb->buffer_size, 0);
  if (nb_read <= 0) {
    rb->buf[0] = '\0';
    rb->start = NULL;
  } else {
    rb->buf[nb_read] = '\0';
    rb->start = rb->buf;
  }
  return (nb_read);
}

std::string gnl_getline(int fd, t_buf *rb) {
  std::string line;

  if (fd < 0 || rb == NULL || rb->buffer_size == 0)
    return (NULL);
  while (1) {
    if (rb->start == NULL || *rb->start == '\0') {
      if (gnl_read_buf(fd, rb) <= 0)
        return (line);
    }
    std::string buf = rb->start;
    size_t nlPos = buf.find_first_of('\n');
    if (nlPos != std::string::npos) {
        line.append(buf.substr(0, nlPos));
        rb->start = rb->start + nlPos + 1;
        return line;
    }
    line.append(buf);
    rb->start = NULL;
  }
}

/** Parse a string to int value using re /' '*[-]d+/
 * @param {const std::string} input
 * @returns {std::pair<int,bool>} .second == false if conversion has failed
 * .first the int value parsed
 */
std::pair<int, bool> ft_atoi(const std::string& str)
{
    bool isNegative = false;
    int digitCount = 0;
    long l = 0;
    std::string::const_iterator it;
    for (it = str.begin(); it != str.end(); ++it) {
        if (*it == ' ')
            continue;
        if (('0' <= *it && *it <= '9')) {
            digitCount++;
            l = (l * 10) + (*it - '0');
            if (l > std::numeric_limits<int>::max())
                return std::pair<int, bool>(0, false);
            continue;
        }
        break;
    }
    if (digitCount == 0)
        return std::pair<int, bool>(0, false);
    if (isNegative)
        l *= -1;
    return std::pair<int, bool>(static_cast<int>(l), true);
}

std::vector<string> readPhrases(const char* filename) {
  std::vector<string> lines;
  if (filename == NULL) return lines;
  std::ifstream is;
  is.open(filename);
  if (!is.is_open()) {
    cerr << "Error: could not open '" << filename << '\'' << endl;
    return lines;
  }
  string line;
  while (std::getline(is, line)) {
    if (line.empty()) continue;
    lines.push_back(line);
  }
  is.close();
  return lines;
}

volatile sig_atomic_t receivedSignal = 0;
void signalHandler(int signum) {
   receivedSignal = signum;
}

void installSigHandler() {
  struct sigaction sigIntAction;
  sigIntAction.sa_handler = signalHandler;
  sigemptyset(&sigIntAction.sa_mask);
  sigIntAction.sa_flags = 0;
  sigaction(SIGINT, &sigIntAction, NULL);
  sigaction(SIGQUIT, &sigIntAction, NULL);
  sigaction(SIGPIPE, &sigIntAction, NULL);
}

ssize_t replyPRIVMSG(string& line, const vector<string>phrases, int sockFD) {
  size_t startPos = line.find_first_of(':');
  size_t endPos = line.find_first_of('!');
  if (startPos == string::npos || endPos == string::npos 
    || startPos >= endPos || startPos == endPos - 1) {
    cerr << "ERROR: empty nick received in PRIVMSG" << endl;
    return 0;
  }
  string nick = line.substr(startPos+1,endPos-startPos-1);
  string reply = "privmsg ";
  reply.append(nick).append(" :").append(phrases[std::rand() % phrases.size()])
    .append("\r\n");
  return send(sockFD,reply.c_str(),reply.length(),MSG_NOSIGNAL);
}

int main(int ac, char* av[]) {
  if (ac != 6) {
    cerr << "Usage: " << av[0] <<" server port pass nick lines-file" << endl;
    return 1;
  }
  char *serverName = av[1];
  std::pair<int,bool> result = ft_atoi(av[2]);
  if (!result.second || result.first > std::numeric_limits<unsigned short>::max()
    || result.first < 1024) {
    cerr << "Invalid port" << endl;
    return 2;
  }
  int port = result.first;
  char *pass = av[3];
  char *nick = av[4];
  std::vector<string> phrases = readPhrases(av[5]);
  if (phrases.empty()) {
    cerr << "Fatal: no phrases found" << endl;
    return 3;
  }
  cerr << "Read " << phrases.size() << " phrases" << endl;
  std::srand(std::time(0));
  struct sockaddr_in serv_addr;

  t_buf b;
  b.buffer_size = 1024;
  b.start = NULL;

  // Create socket
  int sockFD = socket(AF_INET, SOCK_STREAM, 0);
  if (sockFD < 0) {
    cerr << "Socket creation error" << endl;
    return 4;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);

  // Convert IPv4 and IPv6 addresses from text to binary
  if (inet_pton(AF_INET, serverName, &serv_addr.sin_addr) <= 0) {
    cerr << "Invalid address/Address not supported" << endl;
    return 5;
  }

  // Connect to server
  if (connect(sockFD, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    cerr << "Connection Failed" << endl;
    return 6;
  }
  // Send data
  string msg = "pass "; 
  msg.append(pass).append("\r\n")
    .append("nick ").append(nick).append("\r\n")
    .append("user ").append(nick).append(" 0 * :Konfucius\r\n");
  if (send(sockFD, msg.c_str(), msg.length(), MSG_NOSIGNAL) < 0) {
    close(sockFD);
    cerr << "send error login" << endl;
    return 7;
  }

  installSigHandler();
  while (receivedSignal == 0) {
    string line = gnl_getline(sockFD, &b);
    if (line.empty()) {
      continue;
    }
    // :bbb!BBB@127.0.0.1 PRIVMSG aaa :hello
    if (line.find(" PRIVMSG ") != string::npos) {
      if (replyPRIVMSG(line, phrases, sockFD) < 0)
        receivedSignal = -1; 
      continue;
    }
    string errorMsg;
    if (line.find("464 ") != string::npos) {
      errorMsg = "FATAL: Invalid password";
    } else if (line.find("433 ") != string::npos) {
      errorMsg = "FATAL: Nickname already in use";
    }
    if (!errorMsg.empty()) {
      close(sockFD);
      cerr << errorMsg << endl;
      return 9;
    }
  }
  if (receivedSignal != 0) cerr << "Received signal " << receivedSignal << endl;
  bool keepSending = true;
  while (keepSending) {
    string quitMsg = "quit :leaving, ciao\r\n";
    if (send(sockFD,quitMsg.c_str(),quitMsg.length(),MSG_NOSIGNAL) < 0) {
      cerr << "send quit returned < 0" << endl;
    }
    string line = gnl_getline(sockFD, &b);
    keepSending = line.find(":Closing Link:") != string::npos;
  }
  // shutdown(sockFD,SHUT_WR);
  // shutdown(sockFD, SHUT_RD);
  // Close socket
  close(sockFD);
  return 0;
}

