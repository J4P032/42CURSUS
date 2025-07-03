/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:33:04 by jrollon-          #+#    #+#             */
/*   Updated: 2025/07/03 16:41:41 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

class	Fixed{
	public:

	Fixed(void);
	~Fixed(void);

	int		getRawBits(void) const;
	void	setRawBits(int const raw);

	private:
		int					fixedPointNum;
		static const int	fractionBits;
};



#endif
