typedef struct {
	char *map;
	size_t rows, columns;
} Map;

Map map_load(FILE *level);
char *map_at(Map map, size_t row, size_t column);
void map_free(Map *map);
