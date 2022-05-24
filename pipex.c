/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:27:15 by mgordag           #+#    #+#             */
/*   Updated: 2022/05/13 16:25:08 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_child(t_pipex *pipex)
{
	pipex->i = -1;
	while (pipex->cmd_list[++pipex->i])
		free(pipex->cmd_list[pipex->i]);
	free(pipex->cmd_list);
	free(pipex->cmd);
}

void	free_parent(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
}
void	pipex_func(t_pipex pipex, char **av, char **envp)
{
	pid_t		pid1;
	pid_t		pid2;

	pid1 = fork();
	if (pid1 == -1)
		error_messages(2);
	if (pipe(pipex.pipe_fd) == -1)
		error_messages(3);
	if (pid1 == 0)
		child_process(pipex, av, envp);
	pid2 = fork();
	if (pid2 == 0)
		child_process2(pipex, av, envp);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_parent(&pipex);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex pipex;

	(void)ac;
	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[4], O_CREAT | O_TRUNC | O_RDWR, 0000644);
	if (pipex.infile == -1 || pipex.outfile == -1)
		error_messages(1);
	pipex_func(pipex, av, envp);
	return (0);
}
