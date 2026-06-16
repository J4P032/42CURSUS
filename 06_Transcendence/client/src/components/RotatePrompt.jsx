import { useEffect, useState } from 'react';

const MOBILE_MAX_WIDTH = 900;

function isPortraitMobile() {
  if (typeof window === 'undefined') return false;
  return window.innerHeight > window.innerWidth && window.innerWidth < MOBILE_MAX_WIDTH;
}

export default function RotatePrompt() {
  const [show, setShow] = useState(isPortraitMobile);

  useEffect(() => {
    const update = () => setShow(isPortraitMobile());
    window.addEventListener('resize', update);
    window.addEventListener('orientationchange', update);
    return () => {
      window.removeEventListener('resize', update);
      window.removeEventListener('orientationchange', update);
    };
  }, []);

  if (!show) return null;

  return (
    <div className="fixed inset-0 z-[9999] flex flex-col items-center justify-center gap-6 bg-[#0d0d0d] p-6 font-mono text-center text-white">
      <div className="animate-pulse text-6xl" aria-hidden="true">📱↻</div>
      <h2 className="m-0 text-2xl tracking-[2px] text-[#FF6B6B]">ROTATE DEVICE</h2>
      <p className="m-0 max-w-xs text-sm text-[#aaa]">
        GREAT RISK is best played in landscape. Please rotate your device.
      </p>
    </div>
  );
}
