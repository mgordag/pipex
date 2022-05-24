/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgordag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:53:50 by mgordag           #+#    #+#             */
/*   Updated: 2022/05/13 16:11:56 by mgordag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd(t_pipex pipex, char *cmd, char **envp)
{
	char	*command;

	pipex.i = -1;
	pipex.path = get_path(envp);
	pipex.path_list = ft_split(pipex.path, ':');
	while (pipex.path_list[++pipex.i])
	{
		command = ft_strjoin(pipex.path_list[pipex.i], cmd);
		if ((access(command, X_OK) == 0))
			return command;
		free(command);
	}
	return (NULL);
}
char	*get_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (env[i][0] == 'P' && env[i][2] == 'T')
			return (env[i]);
	return (0);
}

void	child_process(t_pipex pipex, char **av, char **envp)
{
	dup2(pipex.infile, STDIN_FILENO);
    dup2(pipex.pipe_fd[1], STDOUT_FILENO);
    close(pipex.pipe_fd[0]);
	pipex.cmd_list = ft_split(av[2], ' ');
	pipex.cmd = get_cmd(pipex, pipex.cmd_list[0], envp);
	printf("%s", pipex.cmd);
	if (!pipex.cmd)
	{
		free_child(&pipex);
	}
	execve(pipex.cmd, pipex.cmd_list, envp);
}
void	child_process2(t_pipex pipex, char **av, char **envp)
{
    dup2(pipex.outfile, 1);
	dup2(pipex.pipe_fd[0], 0);
    close(pipex.pipe_fd[1]);
	pipex.cmd_list = ft_split(av[3], ' ');
	pipex.cmd = get_cmd(pipex, pipex.cmd_list[0], envp);
	printf("%s", pipex.cmd);
	if (!pipex.cmd)
	{
		free_child(&pipex);
	}
	execve(pipex.cmd, pipex.cmd_list, envp);
}

void	error_messages(int code) 
{
	if (code == 1)
	{
		perror ("Error occured on creating files");
		exit(code);
	}
	else if (code == 2)
	{
		perror ("Error occured on fork");
		exit(code);
	}
	else if (code == 3)
	{
		perror ("Error occured on pipe");
		exit(code);
	}
	else if (code == 4)
	{
		perror ("Error occured on dup");
		exit(code);
	}
	else if (code == 5)
	{
		perror ("Error occured on closing files");
		exit(code);
	}
}
