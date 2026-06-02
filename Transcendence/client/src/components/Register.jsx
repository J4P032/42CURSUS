import {api} from '../api';
export default function Register({ onLogin, onBack }) {
  const handleSubmit = async (e) => {
    e.preventDefault();
    const formData = new FormData(e.target);
    const email = formData.get('mail');
    const username = formData.get('username');
    const password = formData.get('password');
    const setError = (msg) => alert(msg);

    try {
      const data = await api.register(email, username, password);
      if (data.ok) {
        onLogin(data.user); // Usuario creado y logueado
      } else {
        setError(data.error || 'Error al registrar');
      }
    } catch (err) {
      setError('Error de conexión');
    }
  };

  return (
    <div style={containerStyle}>
      <h1 style={titleStyle}>GREAT RISK</h1>
      <p style={subtitleStyle}>Please introduce your email, name and password</p>
      
      <form onSubmit={handleSubmit}>
        <label style={labelStyle}>Email</label>
        <input 
          name="mail" 
          type="email"
          autocomplete="off" 
          placeholder="...@..." 
          required 
          style={inputStyle}
        />

		<label style={labelStyle}>Username</label>
        <input 
          name="username" 
          type="text" 
          autocomplete="Username"
          placeholder="..." 
          required 
          style={inputStyle}
        />

		<label style={labelStyle}>Password</label>
        <input 
          name="password" 
          type="password"
          autocomplete="Password" 
          placeholder="..." 
          required 
          style={inputStyle}
        />
        <button type="submit" style={btnStyle}>JOIN</button>
      </form>
	  <button onClick={onBack} style={btnSecondaryStyle}>BACK TO LOGIN</button>
    </div>
  );
}

// ESTILOS COPIADOS DEL LOBBY PARA QUE SEA IDÉNTICO
const containerStyle = {
  maxWidth: '600px',
  margin: '60px auto',
  fontFamily: 'monospace',
  color: 'white',
  backgroundColor: '#1a1a2e',
  padding: '40px',
  borderRadius: '12px',
  border: '2px solid #FF6B6B',
  boxShadow: '0 0 30px rgba(255, 107, 107, 0.3)',
};

const titleStyle = { 
  textAlign: 'center', 
  color: '#FF6B6B',
  marginTop: '0px',
  marginBottom: '4px', 
  letterSpacing: '2px' 
};

const subtitleStyle = { 
  textAlign: 'center', 
  color: '#aaa', 
  paddingTop: '15px',
  marginBottom: '32px', 
};

const labelStyle = { 
  display: 'block', 
  marginBottom: '8px', 
  color: '#FFD700' 
};

const inputStyle = {
  width: '100%',
  padding: '10px',
  backgroundColor: '#333',
  color: 'white',
  border: '2px solid #555',
  borderRadius: '4px',
  fontFamily: 'monospace',
  fontSize: '13px',
  boxSizing: 'border-box',
  marginBottom: '20px',
  textAlign: 'center',
};

const btnStyle = {
  width: '100%',
  padding: '12px',
  backgroundColor: '#FF6B6B',
  color: 'white',
  border: 'none',
  borderRadius: '4px',
  fontFamily: 'monospace',
  fontSize: '14px',
  fontWeight: 'bold',
  cursor: 'pointer',
  marginTop: '10px'
};

const btnSecondaryStyle = {
  ...btnStyle, // Esto copia todo lo de btnStyle
  backgroundColor: '#444', // Pero cambia el color a gris
  marginTop: '20px'
};
