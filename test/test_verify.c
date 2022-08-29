/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_verify.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvieira- <mvieira-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:40:11 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/25 18:18:57 by mvieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <criterion/new/assert.h>
#include <criterion/criterion.h>
#include "../includes/minishell.h"
#include <string.h>



Test(VERIFY_executer_handler, test1_verify)
{
	int fd = open("./test1.txt", O_RDWR);
    char *buf1 = calloc(sizeof(char), 101);
	read(fd, buf1, 100);

	int fd2 = open("./test1original.txt", O_RDWR);
    char *buf2 = calloc(sizeof(char), 101);
	read(fd2, buf2, 100);
	
	cr_expect(strncmp(buf1, buf2, 20) == 0, "outfile is correct");
	close(fd);
}

Test(VERIFY_executer_handler, test2_verify)
{
	int fd = open("./test2.txt", O_RDWR);
    char *buf1 = calloc(sizeof(char), 101);
	read(fd, buf1, 100);

	int fd2 = open("./test2original.txt", O_RDWR);
    char *buf2 = calloc(sizeof(char), 101);
	read(fd2, buf2, 100);
	
	cr_expect(strncmp(buf1, buf2, 20) == 0, "outfile is correct");
	close(fd);
}

Test(VERIFY_executer_handler, test3_verify)
{
	int fd = open("./test3.txt", O_RDWR);
    char *buf1 = calloc(sizeof(char), 101);
	read(fd, buf1, 100);

	int fd2 = open("./test3original.txt", O_RDWR);
    char *buf2 = calloc(sizeof(char), 101);
	read(fd2, buf2, 100);
	
	cr_expect(strncmp(buf1, buf2, 20) == 0, "outfile is correct");
	close(fd);
}

Test(VERIFY_executer_handler, test4_verify)
{
	int fd = open("./test4.txt", O_RDWR);
    char *buf1 = calloc(sizeof(char), 101);
	read(fd, buf1, 100);

	int fd2 = open("./test4original.txt", O_RDWR);
    char *buf2 = calloc(sizeof(char), 101);
	read(fd2, buf2, 100);
	
	cr_expect(strcmp(buf1, buf2) == 0, "outfile is correct");
	close(fd);
}

Test(VERIFY_executer_handler, test5_verify)
{
	int fd = open("./test5.txt", O_RDWR);
    char *buf1 = calloc(sizeof(char), 101);
	read(fd, buf1, 100);

	int fd2 = open("./test5original.txt", O_RDWR);
    char *buf2 = calloc(sizeof(char), 101);
	read(fd2, buf2, 100);
	
	cr_expect(strncmp(buf1, buf2, 15) == 0, "outfile is correct");
	close(fd);
}
/*

Test(VERIFY_executer_handler, test6_verify)
{
	int fd = open("./test6.txt", O_RDWR);
    char *buf1 = calloc(sizeof(char), 101);
	read(fd, buf1, 100);

	int fd2 = open("./test6original.txt", O_RDWR);
    char *buf2 = calloc(sizeof(char), 101);
	read(fd2, buf2, 100);
	
	cr_expect(strcmp(buf1, buf2) == 0, "outfile is correct");
	close(fd);
}
*/

/*
Test(VERIFY_executer_handler, test7_verify)
{
	int fd = open("./test7.txt", O_RDWR);
    char *buf1 = calloc(sizeof(char), 101);
	read(fd, buf1, 100);

	int fd2 = open("./test7original.txt", O_RDWR);
    char *buf2 = calloc(sizeof(char), 101);
	read(fd2, buf2, 100);
	
	cr_expect(strcmp(buf1, buf2) == 0, "outfile is correct");
	close(fd);
}

*/
