export default function Privacy({ onBack }) {
  return (
    <div className="mx-auto my-4 max-h-[92vh] max-w-[700px] overflow-y-auto rounded-xl border-2 border-[#FF6B6B] bg-[#1a1a2e] p-5 font-mono text-white sm:my-10 sm:p-10">
      <h1 className="mb-4 text-center text-xl text-[#FF6B6B] sm:mb-8 sm:text-3xl">PRIVACY POLICY</h1>

      <div className="text-left text-xs leading-[1.6] sm:text-sm">
        <h3 className="mt-5 text-[#FFD700]">1. DATA COLLECTION</h3>
        <p>
          We only collect the strictly necessary data for the operation of ft_transcendence:
          your email address, username, and encrypted password. For 42 school evaluation
          purposes, we also store game statistics and match history.
        </p>

        <h3 className="mt-5 text-[#FFD700]">2. DATA SECURITY</h3>
        <p>
          Your password is never stored in plain text. We use scrypt, a memory-hard key
          derivation function, with a per-user random salt to ensure your credentials are
          protected against unauthorized access.
        </p>

        <h3 className="mt-5 text-[#FFD700]">3. COOKIES AND LOCAL STORAGE</h3>
        <p>
          We use local storage only to maintain your session active. We do not use tracking
          or advertising cookies.
        </p>

        <h3 className="mt-5 text-[#FFD700]">4. DATA SHARING</h3>
        <p>
          Your data is not shared with any third parties. It is stored exclusively within our
          private database environment for the duration of this project's evaluation.
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
