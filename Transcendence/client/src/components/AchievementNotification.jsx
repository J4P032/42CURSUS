import { useState, useEffect } from 'react';
import { ACHIEVEMENTS } from '@trascendence/shared/Achievements';
import '../styles/AchievementNotification.css';

export default function AchievementNotification({ achievementId, onDismiss }) {
  const [isHiding, setIsHiding] = useState(false);
  const achievement = ACHIEVEMENTS[achievementId];

  useEffect(() => {
    const timer = setTimeout(() => {
      setIsHiding(true);
      setTimeout(() => {
        onDismiss?.();
      }, 300); // Match animation duration
    }, 3000); // Show for 3 seconds

    return () => clearTimeout(timer);
  }, [onDismiss]);

  if (!achievement) return null;

  return (
    <div className={`achievement-notification ${isHiding ? 'hiding' : ''}`}>
      <div className="achievement-content">
        <div className="achievement-text">
          <div className="achievement-title">{achievement.name}</div>
          <div className="achievement-description">{achievement.description}</div>
        </div>
      </div>
    </div>
  );
}
