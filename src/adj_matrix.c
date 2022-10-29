/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:13:55 by kpolojar          #+#    #+#             */
/*   Updated: 2022/10/25 15:55:25 by kpolojar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/lemin.h"
#include "../libft/libft.h"

// Function to create an adjacency list from specified edges

// Function to create Adjacency Matrix
void createAdjMatrix(int Adj[][N + 1], int arr[][2], int M)
{
  
    // Initialise all value to this
    // Adjacency list to zero
    for (int i = 0; i < N + 1; i++) {
  
        for (int j = 0; j < N + 1; j++) {
            Adj[i][j] = 0;
        }
    }
  
    // Traverse the array of Edges
    for (int i = 0; i < M; i++) {
  
        // Find X and Y of Edges
        int x = arr[i][0];
        int y = arr[i][1];
  
        // Update value to 1
        Adj[x][y] = 1;
        Adj[y][x] = 1;
    }
}
  
// Function to print the created
// Adjacency Matrix
void printAdjMatrix(int Adj[][N + 1])
{
  
    // Traverse the Adj[][]
    for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < N + 1; j++) {
  
            // Print the value at Adj[i][j]
            ft_putnbr(Adj[i][j]);
        }
        ft_putendl("");
    }
}