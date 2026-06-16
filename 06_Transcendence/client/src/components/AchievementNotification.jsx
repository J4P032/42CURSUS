import { useState, useEffect } from 'react';
import { ACHIEVEMENTS } from '@trascendence/shared/Achievements';

export default function AchievementNotification({ achievementId, onDismiss }) {
  const [isHiding, setIsHiding] = useState(false);
  const achievement = ACHIEVEMENTS[achievementId];

  useEffect(() => {
    const timer = setTimeout(() => {
      setIsHiding(true);
      setTimeout(() => {
        onDismiss?.();
      }, 300);
    }, 3000);

    return () => clearTimeout(timer);
  }, [onDismiss]);

  if (!achievement) return null;

  return (
    <div
      className={`fixed top-5 right-5 z-[1000] min-w-[320px] rounded-lg border-[3px] border-[#FF6B6B] bg-[rgba(20,20,20,0.98)] px-5 py-4 font-mono text-white shadow-[0_0_25px_rgba(255,107,107,0.4),inset_0_0_20px_rgba(255,107,107,0.1)] max-md:top-2.5 max-md:right-2.5 max-md:left-2.5 max-md:min-w-0 ${
        isHiding ? 'animate-slide-out' : 'animate-slide-in'
      }`}
    >
      <div className="flex items-center gap-4">
        <div className="flex flex-col gap-1.5">
          <div className="text-[15px] font-bold uppercase tracking-[1px] text-[#FFD700] [text-shadow:0_0_10px_rgba(255,107,107,0.4)] max-md:text-sm">
            {achievement.name}
          </div>
          <div className="max-w-[270px] text-xs leading-[1.3] text-[#E0E0E0]">
            {achievement.description}
          </div>
        </div>
      </div>
    </div>
  );
}
