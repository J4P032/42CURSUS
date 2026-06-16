import { useState } from 'react';
import { api } from '../api';

const inputClass =
  'mb-3 box-border w-full rounded border-2 border-[#555] bg-[#333] p-2 text-center font-mono text-[13px] text-white sm:mb-5 sm:p-2.5';
const labelClass = 'mb-1 block text-sm text-[#FFD700] sm:mb-2 sm:text-base';

export default function Login({ onLogin, onGoToRegister }) {
  const [error, setError] = useState('');

  const handleSubmit = async (e) => {
    e.preventDefault();
    const formData = new FormData(e.target);
    const email = formData.get('mail');
    const password = formData.get('password');
    setError('');
    try {
      const data = await api.login(email, password);

      if (data.ok) {
        onLogin(data.user);
      } else {
        setError(data.error || 'Credenciales incorrectas');
      }
    } catch (err) {
      setError('Error de conexión con el servidor');
    }
  };

  return (
    <div className="mx-auto my-4 max-w-[600px] rounded-xl border-2 border-[#FF6B6B] bg-[#1a1a2e] p-5 font-mono text-white shadow-[0_0_30px_rgba(255,107,107,0.3)] sm:my-[60px] sm:p-10">
      <h1 className="mt-0 mb-1 text-center text-2xl tracking-[2px] text-[#FF6B6B] sm:text-4xl">GREAT RISK</h1>
      <p className="mb-4 pt-2 text-center text-sm text-[#aaa] sm:mb-8 sm:pt-4 sm:text-base">Login for Battle</p>

      <form onSubmit={handleSubmit}>
        <label className={labelClass}>EMAIL</label>
        <input
          name="mail"
          type="email"
          autoComplete="email"
          placeholder="...@..."
          required
          className={inputClass}
        />

        <label className={labelClass}>PASSWORD</label>
        <input
          name="password"
          type="password"
          autoComplete="current-password"
          placeholder="..."
          required
          className={inputClass}
        />
        <div className="mb-2.5 min-h-[18px] text-center text-xs text-[#ff4444]">{error}</div>
        <button
          type="submit"
          className="mt-2.5 w-full cursor-pointer rounded border-0 bg-[#FF6B6B] p-3 font-mono text-sm font-bold text-white"
        >
          LOGIN
        </button>
      </form>
      <button
        onClick={onGoToRegister}
        className="mt-5 w-full cursor-pointer rounded border-0 bg-[#444] p-3 font-mono text-sm font-bold text-white"
      >
        REGISTER
      </button>
    </div>
  );
}
