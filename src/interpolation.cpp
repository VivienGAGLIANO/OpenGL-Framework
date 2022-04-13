#include "interpolation.h"

Interpolation::Interpolation(const std::string& name, const glm::vec3& v, const glm::vec3& p)
	: CelestBody(name, v, p, glm::vec3(1.0f))
{
	this->U = 0;
	createTable();
}

Interpolation::Interpolation(const std::string& name, const glm::vec3& v, const glm::vec3& p, const glm::vec3& scale)
	: CelestBody(name, v, p, glm::vec3(1.0f))
{
	this->U = 0;
	createTable();
}

void Interpolation::createTable()
{
	// initialiser votre table G(u)- ici avec des points hardcodés
	//PointsControle.push_back(glm::vec3(0.0f,0.0f,0.0f));
	//PointsControle.push_back(glm::vec3(1.0f,0.0f,0.0f));
	PointsControle.push_back(glm::vec3(10.0f, 0.0f, 0.0f));
	PointsControle.push_back(glm::vec3(10.0f, 3.0f, 10.0f));
	PointsControle.push_back(glm::vec3(0.0f, 6.0f, 10.0f));
	PointsControle.push_back(glm::vec3(-10.0f, 4.0f, 10.0f));
	PointsControle.push_back(glm::vec3(-10.0f, 2.0f, 0.0f));
	PointsControle.push_back(glm::vec3(-10.0f, -2.0f, -10.0f));
	PointsControle.push_back(glm::vec3(0.0f, -5.0f, -10.0f));
	PointsControle.push_back(glm::vec3(10.0f, -2.0f, -10.0f));
	PointsControle.push_back(glm::vec3(10.0f, 0.0f, 0.0f));


	float step = 1.0 / GrandeurTable;
	table = (float**)malloc(sizeof(float*) * (GrandeurTable * (PointsControle.size() - 1) + 1));
	table[0] = (float*)malloc(sizeof(float) * 2);
	table[0][0] = 0;
	table[0][1] = 0;

	for (size_t i = 1; i < GrandeurTable * (PointsControle.size() - 1) + 1; i++)
	{
		table[i] = (float*)malloc(sizeof(float) * 2);
		table[i][0] = step * i;

		if (i % GrandeurTable == 0)
			table[i][1] = table[i - GrandeurTable][1] + glm::length(PointsControle[i * step - 1] - PointsControle[i * step]); // TODO : norme a coder dans Util ou glm
	}

	for (size_t i = 1; i < GrandeurTable * (PointsControle.size() - 1); i++)
	{
		int point_ref = i / GrandeurTable;
		float u = i % GrandeurTable * step;

		table[i][1] = table[point_ref * GrandeurTable][1] + (table[(point_ref + 1) * GrandeurTable][1] - table[point_ref * GrandeurTable][1]) * u;
	}
}

float Interpolation::lire_table(float t)
{
	t *= table[GrandeurTable * (PointsControle.size() - 1)][1];

	float s;
	int a = 0, b = GrandeurTable * (PointsControle.size() - 1);

	while (b - a > 1)
	{
		s = table[(a + b) / 2][1];
		if (abs(t - s) < FLT_EPSILON)
		{
			a = (a + b) / 2;
			break;
		}
		if (t < s)
			b = (a + b) / 2;
		if (t > s)
			a = (a + b) / 2;
	}

	float p = (t - table[a][1]) / (table[a + 1][1] - table[a][1]);
	return table[a][0] + p * (table[a + 1][0] - table[a][0]);
}

std::vector<float> Interpolation::coefficient_hermite(float u)
{
	float u3 = pow(u, 3), u2 = u * u;
	float coef[] = {
		2 * u3 - 3 * u2 + 1, -2 * u3 + 3 * u2, u3 - 2 * u2 + u, u3 - u2,	// T(U) * M
		6 * u2 - 6 * u, -6 * u2 + 6 * u, 3 * u2 - 4 * u + 1, 3 * u2 - 2 * u // T(U') * M
	};

	return std::vector<float>(coef, coef + 8);
}

std::pair<glm::vec3, glm::vec3> Interpolation::catmull_rom(float u)
{
	int i = floor(u);
	float du = u - i;
	std::vector<float> coef = coefficient_hermite(du);

	glm::vec3 Pi = PointsControle[i];
	glm::vec3 Pip1 = PointsControle[i + 1];
	glm::vec3 Pi_prime, Pip1_prime;

	if (i == 0)
	{
		if (PointsControle[PointsControle.size() - 1] == PointsControle[0]) // Trajet circulaire
			Pi_prime = (Pip1 - PointsControle[PointsControle.size() - 2]) * 0.5f;
		else
			Pi_prime = (Pip1 - (PointsControle[i + 2] - Pip1) - Pi) * 0.5f;
	}
	else
		Pi_prime = (Pip1 - PointsControle[i - 1]) * .5f;

	if (i == PointsControle.size() - 2)
	{
		if (PointsControle[PointsControle.size() - 1] == PointsControle[0]) // Trajet circulaire
			Pip1_prime = (PointsControle[1] - Pi) * 0.5f;
		else
			Pip1_prime = (Pip1 + (Pi - PointsControle[i - 1]) - Pi) * 0.5f;
	}
	else
		Pip1_prime = (PointsControle[i + 2] - Pi) * 0.5f;

	glm::vec3 PO = coef[0] * Pi + coef[1] * Pip1 + coef[2] * Pi_prime + coef[3] * Pip1_prime;
	glm::vec3 VN = (coef[4] * Pi + coef[5] * Pip1 + coef[6] * Pi_prime + coef[7] * Pip1_prime) - glm::vec3(0, 0, 0);

	return std::pair<glm::vec3, glm::vec3>(PO, VN);
}


glm::vec3 Interpolation::cat_rom(float t_norm) // � compl�ter
{
	float u = t_norm * table[GrandeurTable * (PointsControle.size() - 1)][0];
	auto p = catmull_rom(u);

	PO = p.first;
	VN = p.second;
	return PO;
}


glm::vec3 Interpolation::cat_rom_t(float t_norm) // � compl�ter
{
	float u = lire_table(t_norm);
	auto p = catmull_rom(u);

	PO = p.first;
	VN = p.second;
	return PO;
}

void Interpolation::setPosition(const glm::vec3& pos) {
	this->prevPosition = this->position;
	this->position = pos;
}