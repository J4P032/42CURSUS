import { api } from '../api';

const inputClass =
  'mb-3 box-border w-full rounded border-2 border-[#555] bg-[#333] p-2 text-center font-mono text-[13px] text-white sm:mb-5 sm:p-2.5';
const labelClass = 'mb-1 block text-sm text-[#FFD700] sm:mb-2 sm:text-base';

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
        onLogin(data.user);
      } else {
        setError(data.error || 'Error al registrar');
      }
    } catch (err) {
      setError('Error de conexión');
    }
  };

  return (
    <div className="mx-auto my-4 max-w-[600px] rounded-xl border-2 border-[#FF6B6B] bg-[#1a1a2e] p-5 font-mono text-white shadow-[0_0_30px_rgba(255,107,107,0.3)] sm:my-[60px] sm:p-10">
      <h1 className="mt-0 mb-1 text-center text-2xl tracking-[2px] text-[#FF6B6B] sm:text-4xl">GREAT RISK</h1>
      <p className="mb-4 pt-2 text-center text-sm text-[#aaa] sm:mb-8 sm:pt-4 sm:text-base">
        Please introduce your email, name and password
      </p>

      <form onSubmit={handleSubmit}>
        <label className={labelClass}>Email</label>
        <input
          name="mail"
          type="email"
          autoComplete="email"
          placeholder="...@..."
          required
          className={inputClass}
        />

        <label className={labelClass}>Username</label>
        <input
          name="username"
          type="text"
          autoComplete="username"
          placeholder="Min 3 characters"
          required
          minLength={3}
          className={inputClass}
        />

        <label className={labelClass}>Password</label>
        <input
          name="password"
          type="password"
          autoComplete="new-password"
          placeholder="Min 6 characters"
          required
          minLength={6}
          className={inputClass}
        />
        <button
          type="submit"
          className="mt-2.5 w-full cursor-pointer rounded border-0 bg-[#FF6B6B] p-3 font-mono text-sm font-bold text-white"
        >
          JOIN
        </button>
      </form>
      <button
        onClick={onBack}
        className="mt-5 w-full cursor-pointer rounded border-0 bg-[#444] p-3 font-mono text-sm font-bold text-white"
      >
        BACK TO LOGIN
      </button>
    </div>
  );
}
