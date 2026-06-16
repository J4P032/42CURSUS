/**
 * Validates that all territory connections are bilateral
 * Run with: npm run validate:territories
 */

import { TERRITORIES } from './Territories.js';

function validateConnections() {
  const errors = [];

  // Check for bilateral connections
  for (const [territory, data] of Object.entries(TERRITORIES)) {
    for (const neighbor of data.neighbors) {
      if (!TERRITORIES[neighbor]) {
        errors.push(`❌ ${territory} has neighbor "${neighbor}" but "${neighbor}" doesn't exist`);
      } else if (!TERRITORIES[neighbor].neighbors.includes(territory)) {
        errors.push(`❌ ${territory} → ${neighbor} (not reciprocated)`);
      }
    }
  }

  // Report results
  if (errors.length === 0) {
    return true;
  } else {
    return false;
  }
}

validateConnections();
