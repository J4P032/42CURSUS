/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:47:52 by jrollon-          #+#    #+#             */
/*   Updated: 2025/06/14 20:47:55 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_CLASS_HPP
# define CONTACT_CLASS_HPP

# include <string>

class	Contact
{
	public:
		Contact(void);
		~Contact(void);

		void	setFirstName(std::string name);
		void	setLastName(std::string surname);
		void	setNickname(std::string nick);
		void	setPhoneNumber(std::string phone);
		void	setDarkestSecret(std::string secret);

		std::string	getFirstName(void) const; //const for not modifying it by accident
		std::string	getLastName(void) const;
		std::string getNickname(void) const;
		std::string	getPhoneNumber(void) const;
		std::string	getDarkestSecret(void) const;
	
	private:
		std::string	_firstName;
		std::string	_lastName;
		std::string	_nickname;
		std::string	_phoneNumber;
		std::string	_darkestSecret;
};

#endif
