export const ACHIEVEMENTS = {
  first_blood: {
    id: 'first_blood',
    name: 'First Blood',
    description: 'Conquer your first territory',
    condition: (stats) => stats.territoriesConquered >= 1,
  },
  conqueror: {
    id: 'conqueror',
    name: 'Conqueror',
    description: 'Conquer 10 territories in a single game',
    condition: (stats) => stats.territoriesConquered >= 10,
  },
  survivor: {
    id: 'survivor',
    name: 'Survivor',
    description: 'Win a game that reaches the turn limit',
    condition: (stats) => stats.wonByScore === true,
  },
  dominator: {
    id: 'dominator',
    name: 'Dominator',
    description: 'Win by capturing all enemy capitals',
    condition: (stats) => stats.wonByCapitals === true,
  },
  veteran: {
    id: 'veteran',
    name: 'Veteran',
    description: 'Play 5 games',
    condition: (stats) => stats.gamesPlayed >= 5,
  },
  
  better_than_napoleon: {
  id: 'better_than_napoleon',
  name: 'Better than Napoleon',
  description: 'As France, conquer Moscow and London',
  faction: 'france',
  condition: (stats) => 
    stats.territoriesConquered_ids?.includes('moscow') && 
    stats.territoriesConquered_ids?.includes('england'),
  },
	we_dont_need_prussians: {
	id: 'we_dont_need_prussians',
	name: "We Don't Need the Prussians",
	description: 'As England, conquer the Low Countries, Belgium and France',
	faction: 'england',
	condition: (stats) =>
		['batavia', 'belgium', 'france'].every(t => 
		stats.territoriesConquered_ids?.includes(t)
		),
	},
	not_another_austerlitz: {
		id: 'not_another_austerlitz',
		name: 'Not Another Austerlitz',
		description: 'As Russia, conquer Vienna, Hungary and Bohemia',
		faction: 'russia',
		condition: (stats) =>
			['austria', 'hungary', 'bohemia'].every(t => 
				stats.territoriesConquered_ids?.includes(t)
			),
	},
	nightmare_of_napoleon: {
		id: 'nightmare_of_napoleon',
		name: 'The Nightmare of Napoleon',
		description: 'As Spain, conquer France, Belgium and Piedmont',
		faction: 'spain',
		condition: (stats) =>
			['france', 'belgium', 'piemonte'].every(t => 
				stats.territoriesConquered_ids?.includes(t)
			),
	},

	not_winged: {
		id: 'not_winged',
		name: "Not so winged, huh?",
		description: 'As the Ottomans, conquer Vienna and Poland',
		faction: 'ottoman',
		condition: (stats) =>
			['poland', 'austria'].every(t => 
				stats.territoriesConquered_ids?.includes(t)
			),
	},

	empire_strikes_back: {
		id: 'empire_strikes_back',
		name: "The Empire Strikes Back",
		description: 'As the Austrians, conquer the former Holy Roman Empire provinces',
		faction: 'austria',
		condition: (stats) =>
			['piemonte', 'lombardia', 'venetia', 'saxony', 'helvetia', 'bavaria', 'hanover', 'rhine_west', 'brandenburg'].every(t => 
				stats.territoriesConquered_ids?.includes(t)
			),
	},

	spanish_empire: {
		id: 'spanish_empire',
		name: "Imperio Español",
		description: 'As Spain, recover the Habsburgian provinces',
		faction: 'spain',
		condition: (stats) =>
			['naples', 'lombardia', 'batavia', 'belgium'].every(t => 
				stats.territoriesConquered_ids?.includes(t)
			),
	},
	
	north_sea_empire: {
		id: 'north_sea_empire',
		name: 'North Sea Empire',
		description: 'As England, control Scandinavia while keeping the British Isles',
		faction: 'england',
		condition: (stats, territoryOwners) =>
			['sweden', 'norway', 'denmark', 'england', 'scotland', 'ireland'].every(t =>
				territoryOwners[t] === 'england'
			),
	},

	malcom_life_finds_a_way: {
		id: 'life_finds_a_way',
		name: "That Crazy Son of a Bitch Did It",
		description: 'As France, conquer all of Spain and Moscow',
		faction: 'france',
		condition: (stats, territoryOwners) =>
			['spain', 'catalonia', 'portugal', 'moscow'].every(t =>
				territoryOwners[t] === 'france'
			),
	},

	third_rome: {
		id: 'third_rome',
		name: "True Third Rome",
		description: 'As Russia, conquer Constantinople and Rome',
		faction: 'russia',
		condition: (stats) =>
			['constantinople', 'rome'].every(t => 
				stats.territoriesConquered_ids?.includes(t)
			),
	},

	third_crusade: {
		id: 'third_crusade',
		name: "Third Crusade",
		description: 'As England, conquer Levant and Egypt',
		faction: 'england',
		condition: (stats) =>
			['levant', 'egypt'].every(t => 
				stats.territoriesConquered_ids?.includes(t)
			),
	},

	king_jerusalem: {
		id: 'king_jerusalem',
		name: "Rey de Jerusalén",
		description: 'As Spain, honor your title and conquer Levant',
		faction: 'spain',
		condition: (stats) =>
			['levant'].every(t => 
				stats.territoriesConquered_ids?.includes(t)
			),
	},
};

/**
 * Checks which achievements a player has newly unlocked.
 * @param {Object} stats - current player stats
 * @param {string[]} alreadyUnlocked - achievement ids already unlocked
 * @returns {string[]} newly unlocked achievement ids
 */
export function checkAchievements(stats, territoryOwners, alreadyUnlocked = []) {
  return Object.values(ACHIEVEMENTS)
    .filter(a => !alreadyUnlocked.includes(a.id))
    .filter(a => !a.faction || a.faction === stats.faction)
    .filter(a => a.condition(stats, territoryOwners))
    .map(a => a.id);
}