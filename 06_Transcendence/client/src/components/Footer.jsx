export default function Footer({ onPrivacy, onTerms }) {
  return (
    <footer className="w-full border-t border-[#333] bg-[#0a0a1a] py-4 text-center font-mono text-xs text-[#888]">
      <span
        onClick={onPrivacy}
        className="cursor-pointer text-[#aaa] underline transition-colors duration-200 hover:text-white"
      >
        Privacy Policy
      </span>
      <span className="mx-4 text-[#555]">|</span>
      <span
        onClick={onTerms}
        className="cursor-pointer text-[#aaa] underline transition-colors duration-200 hover:text-white"
      >
        Terms of Service
      </span>
    </footer>
  );
}
