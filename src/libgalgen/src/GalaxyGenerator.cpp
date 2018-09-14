#include "Vector3Array.h"
#include "BaseGenerator.h"
#include "GalaxyGenerator.h"
#include "Mutator.h"

using namespace GalGen;

const std::vector<Vector3> GalaxyGenerator::generateRegularSpiralGalaxy()
{
	// TODO: Template this
    const double NUMBER_OF_STARS{ 5000 };
	const double GALAXY_DIAMETER{ 1.0 };
	const double GALAXY_THICKNESS{ GALAXY_DIAMETER * 0.2 };
	const double NUMBER_OF_STARS_IN_BULGE{ NUMBER_OF_STARS * 0.2 };
	const double NUMBER_OF_STARS_IN_SPHEROID{ NUMBER_OF_STARS * 0.1 };
	const double NUMBER_OF_STARS_IN_ARMS{ NUMBER_OF_STARS - NUMBER_OF_STARS_IN_BULGE - NUMBER_OF_STARS_IN_SPHEROID };
	const double ROTATION_FACTOR_POWER{ 0.05 };
	const double ROTATION_FACTOR_LINEAR{ 1.0 };

//    const double NUMBER_OF_STARS{ 100 };
//    const double GALAXY_DIAMETER{ 0.5 };
//    const double GALAXY_THICKNESS{ GALAXY_DIAMETER * 0.2 };
//    const double NUMBER_OF_STARS_IN_BULGE{ NUMBER_OF_STARS * 0.2 };
//    const double NUMBER_OF_STARS_IN_SPHEROID{ NUMBER_OF_STARS * 0.1 };
//    const double NUMBER_OF_STARS_IN_ARMS{ NUMBER_OF_STARS - NUMBER_OF_STARS_IN_BULGE - NUMBER_OF_STARS_IN_SPHEROID };
//    const double ROTATION_FACTOR_POWER{ 0.03 };
//    const double ROTATION_FACTOR_LINEAR{ 0.8 };

	Vector3Array galaxy;

	// create bulge
	BaseGenerator generator(static_cast<unsigned int>(NUMBER_OF_STARS_IN_BULGE), 0.8);
	generator.setScale(Vector3{ GALAXY_THICKNESS, GALAXY_THICKNESS, GALAXY_THICKNESS });
	galaxy.addPoints(generator.generate(BoundingVolume::BV_SPHERE));
	
	// create spheroid
	generator.setDeviation(2.0);
	generator.setPointsNum(static_cast<unsigned int>(NUMBER_OF_STARS_IN_SPHEROID));
	generator.setScale(Vector3{ GALAXY_DIAMETER, GALAXY_DIAMETER, GALAXY_THICKNESS });
	galaxy.addPoints(generator.generate(BoundingVolume::BV_SPHERE));
	
	generator.setDeviation(1.0);
	// creat arm 1
	generator.setPointsNum(static_cast<unsigned int>(NUMBER_OF_STARS_IN_ARMS / 4.0));
	generator.setScale(Vector3{ GALAXY_DIAMETER / 2.0, GALAXY_THICKNESS, GALAXY_THICKNESS / 2.0 });
	generator.setTranslation(Vector3{ - GALAXY_DIAMETER / 2.0, 0.0, 0.0 });
	galaxy.addPoints(generator.generate(BoundingVolume::BV_SPHERE));
	
	// create arm 2
	generator.setScale(Vector3{ GALAXY_DIAMETER / 2.0, GALAXY_THICKNESS, GALAXY_THICKNESS / 2.0 });
	generator.setTranslation(Vector3{ GALAXY_DIAMETER / 2.0, 0.0, 0.0 });
	galaxy.addPoints(generator.generate(BoundingVolume::BV_SPHERE));

	// create arm 3
	generator.setScale(Vector3{ GALAXY_THICKNESS, GALAXY_DIAMETER / 2.0, GALAXY_THICKNESS / 2.0 });
	generator.setTranslation(Vector3{ 0.0, GALAXY_DIAMETER / 2.0, 0.0 });
	galaxy.addPoints(generator.generate(BoundingVolume::BV_SPHERE));

	// create arm 4
	generator.setScale(Vector3{ GALAXY_THICKNESS, GALAXY_DIAMETER / 2.0, GALAXY_THICKNESS / 2.0 });
	generator.setTranslation(Vector3{ 0.0, -GALAXY_DIAMETER / 2.0, 0.0 });
	galaxy.addPoints(generator.generate(BoundingVolume::BV_SPHERE));

	// swirl galaxy
	galaxy = Mutator::swirlXY(galaxy, ROTATION_FACTOR_POWER, ROTATION_FACTOR_LINEAR);

	return galaxy.getPoints();
}

const std::vector<Vector3> GalaxyGenerator::generateToonSpiralGalaxy()
{
    const double NUMBER_OF_STARS{ 20.0 };
    const double NUMBER_OF_ARMS{ 2.0 };
    const double ARM_LENGTH{ PI };
    const double DEVIATION{ 1.0 };
    const double DISTRIBUTION_SCALE_FACTOR{ 0.01 };

    Vector3Array galaxy;
    std::vector<Vector3> points {};

    auto distribution = std::normal_distribution<double>(0, DEVIATION);
    std::default_random_engine generator;

    const double LINEAR_ARM_STEP { ARM_LENGTH / (NUMBER_OF_STARS / NUMBER_OF_ARMS) };
    const double ANGULAR_ARM_STEP { 2 * PI / NUMBER_OF_ARMS };

    double r{ 0.0 };
    double phi{ 0.0 };
    double k { 0.1 };

    while (phi < ARM_LENGTH)
    {
        phi += LINEAR_ARM_STEP;
        r = k * phi;
        for (int j = 0; j < NUMBER_OF_ARMS; ++j) {
            double dx { distribution(generator) * DISTRIBUTION_SCALE_FACTOR };
            double dy { distribution(generator) * DISTRIBUTION_SCALE_FACTOR };
            double x = r * cos(phi + ANGULAR_ARM_STEP * j) + dx;
            double y = r * sin(phi + ANGULAR_ARM_STEP * j) + dy;
            Vector3 v{x, y, 0};
            points.push_back(v);
        }
    }

    return points;
}
