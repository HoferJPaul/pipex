/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:17:03 by phofer            #+#    #+#             */
/*   Updated: 2025/10/08 15:44:06 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	init_pipex(); //fill struct with default data. Valgrind safety.
	check_args(); //opens all files needed and handles here_doc
					//custom GNL
	parse_cmds();  //ft_parse_cmds will create an array like this:
					//["/bin/cat", "/usr/bin/head", "/usr/bin/wc"]
	parse_args();  // use ft_split to yield a 2D array like this one:
					//[["cat"], ["head", "-n", "5"], ["wc", "-l"]]
	while (cmds)
		ft_exec();  //where the magic happens

	return (0);
}
