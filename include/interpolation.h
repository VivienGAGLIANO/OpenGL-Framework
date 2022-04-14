#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "CelestBody.h"
#include <glm.hpp>
#include <vector>

class Interpolation : public CelestBody
{
	public:
		Interpolation(const std::string& name, const glm::vec3& v, const glm::vec3& p);
		Interpolation(const std::string& name, const glm::vec3& v, const glm::vec3& p, const glm::vec3& scale);
		void setPosition(const glm::vec3& pos);
		void createTable();
		float lire_table(float t);
		std::vector<float> coefficient_hermite(float u);
		std::pair<glm::vec3, glm::vec3> catmull_rom(float u);
		glm::vec3 cat_rom(float t_norm);
		glm::vec3 cat_rom_t(float t_norm);
	
		int getNbPoints();

	private:
		glm::vec3 PO;
		glm::vec3 VN;
		std::vector<glm::vec3> PointsControle;
		int nbPoints = 0;
		float U;
		float** table;
		const int GrandeurTable = 100; // Grandeur de la table pour la fonction u=U(s)

};

#endif