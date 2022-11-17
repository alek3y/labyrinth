#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include "player.h"
#include "ai.h"

struct Neighbor {
	size_t i;
	long dx, dy;
	bool valid;
};

void ai_neighbors(struct Neighbor *list, Map map, size_t index) {
	struct Neighbor neighbors[4] = {
		{.dx = 0, .dy = -1, .i = index - map.columns, .valid = index >= map.columns},
		{.dx = 0, .dy = 1, .i = index + map.columns, .valid = index + map.columns < map.rows * map.columns},
		{.dx = -1, .dy = 0, .i = index-1, .valid = index % map.columns > 0},
		{.dx = 1, .dy = 0, .i = index+1, .valid = index % map.columns < map.columns-1}
	};

	memcpy(list, neighbors, sizeof(neighbors));
}

struct Node {
	long distance;
	size_t previous;
	bool has_previous, visited;
};

//! @details Anche se la funzione produce un percorso comunque accettabile sui
//! vari test effettuati, l'algoritmo per la shortest-path di Dijkstra non è
//! fatto per grafi con pesi negativi, e di conseguenza il metodo non è del
//! tutto corretto. Un'alternativa sarebbe Bellman-Ford, ma non permette cicli
//! negativi (cicli tra i nodi del grafo che hanno la somma dei pesi negativa).
//! Sembrerebbe che trovare il percorso minimo con cicli negativi sia un problema
//! senza soluzioni efficienti.
Steps ai_steps(Player source, Map map) {

	// Trova l'uscita sulla mappa e la imposta come destinazione della ricerca
	size_t target = 0;
	MAP_ITERATE(map, i, x, y) {
		if (*map_at(map, x, y) == map.exit) {
			target = i;
			break;
		}
	}

	// Inizializza i pesi a Inf per cercare il percorso con lo score migliore
	struct Node *distances = malloc(map.rows * map.columns * sizeof(*distances));
	for (size_t i = 0; i < map.rows * map.columns; i++) {
		distances[i] = (struct Node) {
			.distance = LONG_MAX,
			.previous = 0,	// Nodo precedente che porta allo score migliore
			.has_previous = false,
			.visited = false
		};

		// Toglie le celle con cui avvengono le collisioni dal grafo da visitare
		if (strchr(map.collisions, map.map[i]) != NULL) {
			distances[i].visited = true;
		}
	}
	distances[source.y * map.columns + source.x].distance = 0;	// Il giocatore è il primo nodo da visitare

	struct Neighbor neighbors[4];	// Alloca lo spazio per salvare i vicini
	for (size_t k = 0; k < map.rows * map.columns; k++) {	// Il totale di nodi da visitare è la cardinalità del grafo

		// Trova il nodo con lo score migliore
		size_t visiting = 0;
		for (size_t i = 1; i < map.rows * map.columns; i++) {
			if (!distances[i].visited && distances[i].distance < distances[visiting].distance) {
				visiting = i;
			}
		}

		// Finisci la ricerca se è stata trovata l'uscita
		if (visiting == target) {
			break;
		}

		// Trova i vicini del nodo visiting e salvali
		ai_neighbors(neighbors, map, visiting);

		// Aggiorna il peso dei vicini
		for (size_t i = 0; i < 4; i++) {
			if (!neighbors[i].valid || distances[neighbors[i].i].visited) {
				continue;
			}

			Player from_visiting = {
				.x = visiting % map.columns,
				.y = visiting / map.columns,
				.score = distances[visiting].distance
			};

			long distance = from_visiting.score;
			player_step(
				&from_visiting,
				neighbors[i].dx,
				neighbors[i].dy,
				map
			);
			distance += -(from_visiting.score - distance);

			if (distance < distances[neighbors[i].i].distance) {
				distances[neighbors[i].i].distance = distance;
				distances[neighbors[i].i].previous = visiting;
				distances[neighbors[i].i].has_previous = true;
			}
		}

		// Imposta il nodo trovato come visitato
		distances[visiting].visited = true;
	}

	Steps steps = {.length = 1};

	size_t visiting = target;
	while (distances[visiting].has_previous) {
		visiting = distances[visiting].previous;
		steps.length++;
	}

	visiting = target;
	steps.steps = malloc(steps.length * sizeof(*steps.steps));	// Adatta la lista di step
	for (size_t i = 0; i < steps.length-1; i++) {
		visiting = distances[visiting].previous;
		steps.steps[steps.length-i-2] = visiting;	// Metti gli indici partendo dal penultimo step
	}
	steps.steps[steps.length-1] = target;

	free(distances);
	return steps;
}

void ai_free(Steps *steps) {
	assert(steps->steps != NULL);

	free(steps->steps);
	memset(steps, 0, sizeof(*steps));
}
