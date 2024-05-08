#ifndef PERFORMANCE_H
#define PERFORMANCE_H


class Performance
{
public:
	~Performance();

	static void initialize();
	static void deinitialize();

	static unsigned int get_vertex_count();
	static void increment_vertex_count(unsigned int count);
	static void reset_vertex_count();

	static unsigned int get_index_count();
	static void increment_index_count(unsigned int count);
	static void reset_index_count();

private:
	Performance();

	static Performance *instance;
	unsigned int vertex_count = 0;
	unsigned int index_count = 0;
};

#endif // PERFORMANCE_H