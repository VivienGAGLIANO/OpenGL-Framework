#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "CelestBody.h"
#include <glm.hpp>
#include <vector>

class Interpolation : CelestBody
{
	public:
		Interpolation(const std::string& name, const glm::vec3& v, const glm::vec3& p);
		Interpolation(const std::string& name, const glm::vec3& v, const glm::vec3& p, const glm::vec3& scale);
		void createTable();
		float lire_table(float t);
		void saut(float t, glm::vec3& PO);
		void inter_lin(float t_norm, glm::vec3& PO, glm::vec3& VN);
		std::vector<float> coefficient_hermite(float u);
		std::pair<glm::vec3, glm::vec3> catmull_rom(float u);
		void cat_rom(float t_norm, glm::vec3& PO, glm::vec3& VN);
		void cat_rom_t(float t_norm, glm::vec3& PO, glm::vec3& VN);

	private:
		glm::vec3 PO;
		glm::vec3 VN;
		const int GrandeurTable = 100; // Grandeur de la table pour la fonction u=U(s)
		std::vector<glm::vec3> PointsControle;
		float** table;
};

#endif