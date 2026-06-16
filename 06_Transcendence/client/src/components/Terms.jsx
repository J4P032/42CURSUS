export default function Terms({ onBack }) {
  return (
    <div className="mx-auto my-4 max-h-[92vh] max-w-[700px] overflow-y-auto rounded-xl border-2 border-[#FF6B6B] bg-[#1a1a2e] p-5 font-mono text-white sm:my-10 sm:p-10">
      <h1 className="mb-4 text-center text-xl text-[#FF6B6B] sm:mb-8 sm:text-3xl">TERMS OF SERVICE</h1>

      <div className="text-left text-xs leading-[1.6] sm:text-sm">
        <h3 className="mt-5 text-[#FFD700]">1. ACCEPTANCE OF TERMS</h3>
        <p>
          By accessing ft_transcendence, you agree to follow the rules of the 42 community.
          This platform is an educational project created for the 42 Common Core.
        </p>

        <h3 className="mt-5 text-[#FFD700]">2. FAIR PLAY</h3>
        <p>
          Hacking, cheating, or intentionally exploiting bugs is strictly prohibited. The
          game is designed to test strategy and skill, not exploit-finding abilities.
        </p>

        <h3 className="mt-5 text-[#FFD700]">3. CODE OF CONDUCT</h3>
        <p>
          Bullying, hate speech, or harassment in the global chat will result in an immediate
          account suspension. Respect your fellow students as per the 42 Pedagogy standards.
        </p>

        <h3 className="mt-5 text-[#FFD700]">4. LIMITATION OF LIABILITY</h3>
        <p>
          This software is provided "as is", without warranty of any kind. The developers are
          not responsible for any data loss or "emotional damage" caused by losing a game of
          Risk.
        </p>

        <h3 className="mt-5 text-[#FFD700]">5. ACCOUNT TERMINATION</h3>
        <p>
          We reserve the right to terminate accounts that violate these terms or the general
          spirit of the 42 Network.
        </p>
      </div>

      <button
        onClick={onBack}
        className="mx-auto mt-8 block cursor-pointer border-0 bg-[#444] px-5 py-2.5 text-white"
      >
        GO BACK
      </button>
    </div>
  );
}
