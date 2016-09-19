#include "TrussType.h"
#include "BeamType.h"
#include "InternalStructuralElementObjectTests.h"

CPPUNIT_TEST_SUITE_REGISTRATION(InternalStructuralElementObjectTest);

InternalStructuralElementObjectTest::InternalStructuralElementObjectTest(){
}

InternalStructuralElementObjectTest::~InternalStructuralElementObjectTest(){
}

void InternalStructuralElementObjectTest::setUp(){
}

void InternalStructuralElementObjectTest::tearDown(){
}

void InternalStructuralElementObjectTest::types_test(){
	CPPUNIT_ASSERT_MESSAGE("TrussType must have a DOF equals to 3", TrussType::NDOF == 3 );
	CPPUNIT_ASSERT_MESSAGE("BeamType must have a DOF equals to 6", BeamType::NDOF == 6 );
}

/*
 * basic_test
 */
void InternalStructuralElementObjectTest::basic_test(){
	Point* start = PointManager::GetInstance().GetPoint(0.0, 0.0, 0.0);
	Point* end = PointManager::GetInstance().GetPoint(1.0, 1.0, 1.0);
	double cross_sec = 2.5;

	InternalTrussElement obj_t = InternalTrussElement(start,end,cross_sec,BASIC);
	InternalBeamElement obj_b = InternalBeamElement(start,end,cross_sec,BASIC);
}

	/*
	 * getter_test
	 */
void InternalStructuralElementObjectTest::getter_test(){
	Point* start = PointManager::GetInstance().GetPoint(0.0, 0.0, 0.0);
	Point* end = PointManager::GetInstance().GetPoint(1.0, 1.0, 1.0);
	double cross_sec = 2.5;

	InternalTrussElement obj_t = InternalTrussElement(start,end,cross_sec,BASIC);
	InternalBeamElement obj_b = InternalBeamElement(start,end,cross_sec,BASIC);

	CPPUNIT_ASSERT_MESSAGE("Each Internal Truss Element Object must have 2 points",
			obj_t.GetNumberOfPoints() == 2);
	CPPUNIT_ASSERT_MESSAGE("Each Internal Beam Element Object must have 2 points",
			obj_b.GetNumberOfPoints() == 2);

	CPPUNIT_ASSERT_EQUAL_MESSAGE("The stiffness should a 6x6 matrix for TrussType",
			36,static_cast<int>(obj_t.GetLocalStiffnessMatrix().n_elem));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("The displacement vector should be 1x6 for TrussType",
			6,static_cast<int>(obj_t.GetNodalDisplacementInLocalCoordinates().n_elem));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("The element forces vect should be 1x3 for TrussType",
			3,static_cast<int>(obj_t.GetElementForcesInLocalCoordinates().n_elem));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("The element forces vect should be 6x6 for TrussType",
			36,static_cast<int>(obj_t.GetTransformationMatrix().n_elem));


	CPPUNIT_ASSERT_EQUAL_MESSAGE("The stiffness should a 12x12 matrix for BeamType",
			144,static_cast<int>(obj_b.GetLocalStiffnessMatrix().n_elem));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("The displacement vector should be 1x12 for BeamType",
			12,static_cast<int>(obj_b.GetNodalDisplacementInLocalCoordinates().n_elem));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("The element forces vect should be 1x6 for BeamType",
			6,static_cast<int>(obj_b.GetElementForcesInLocalCoordinates().n_elem));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("The transformation matrix should be 12x12 for BeamType",
			144,static_cast<int>(obj_b.GetTransformationMatrix().n_elem));
}

/*
 * length_test
 */
void InternalStructuralElementObjectTest::length_test(){
	Point* start = PointManager::GetInstance().GetPoint(0.0, 0.0, 0.0);
	Point* end = PointManager::GetInstance().GetPoint(1.0, 1.0, 0.0);
	double cross_sec = 2.5;

	InternalTrussElement obj_t = InternalTrussElement(start,end,cross_sec,BASIC);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("The length must be sqrt(2)",sqrt(2),
			obj_t.GetLength());

	end =  PointManager::GetInstance().GetPoint(1.0, 1.0, 1.0);
	InternalTrussElement obj_t2 = InternalTrussElement(start,end,cross_sec,BASIC);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("The length must be sqrt(3)",sqrt(3),
			obj_t2.GetLength());
}

/*
 * truss_transformation_test
 */
void InternalStructuralElementObjectTest::truss_transformation_test(){
	Point* start = PointManager::GetInstance().GetPoint(0.0, 0.0, 0.0);
	Point* end = PointManager::GetInstance().GetPoint(1.0, 0.0, 0.0);
	double cross_sec = 2.5;
	arma::umat test;

	InternalTrussElement obj_t = InternalTrussElement(start,end,cross_sec,BASIC);
	TransformationMatrixType expected = {
					{1.0, 0.0, 0.0, 0.0, 0.0, 0.0},
					{0.0, 1.0, 0.0, 0.0, 0.0, 0.0},
					{0.0, 0.0, 1.0, 0.0, 0.0, 0.0},
					{0.0, 0.0, 0.0, 1.0, 0.0, 0.0},
					{0.0, 0.0, 0.0, 0.0, 1.0, 0.0},
					{0.0, 0.0, 0.0, 0.0, 0.0, 1.0}
	};
	test = obj_t.GetTransformationMatrix() == expected;
	CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(
			"We expect the binary matrix to have the element 1 at each position",
			36.0,
			sum(sum(test,1)),
			0
	);


	end = PointManager::GetInstance().GetPoint(0.0, 1.0, 0.0);
	InternalTrussElement obj_t2 = InternalTrussElement(start,end,cross_sec,BASIC);
	expected = {
					{0.0, -1.0, 0.0, 0.0,  0.0, 0.0},
					{1.0,  0.0, 0.0, 0.0,  0.0, 0.0},
					{0.0,  0.0, 1.0, 0.0,  0.0, 0.0},
					{0.0,  0.0, 0.0, 0.0, -1.0, 0.0},
					{0.0,  0.0, 0.0, 1.0,  0.0, 0.0},
					{0.0,  0.0, 0.0, 0.0,  0.0, 1.0}
	};
	test = arma::abs(obj_t2.GetTransformationMatrix() - expected)<1E-6;
	CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(
			"We expect the binary matrix to have the element 1 at each position",
			36.0,
			sum(sum(test,1)),
			0
	);

	float px = 4.0, py = 6.0, pz = 0.0;
	end =  PointManager::GetInstance().GetPoint(px,py,pz);
	InternalTrussElement obj_t3 = InternalTrussElement(start,end,cross_sec,BASIC);
	expected = {
					{cos(atan(py/px)),-sin(atan(py/px)) , 0.0, 0.0,  0.0, 0.0},
					{sin(atan(py/px)), cos(atan(py/px)), 0.0, 0.0,  0.0, 0.0},
					{0.0,  0.0, 1.0, 0.0,  0.0, 0.0},
					{0.0,  0.0, 0.0, cos(atan(py/px)),-sin(atan(py/px)), 0.0},
					{0.0,  0.0, 0.0, sin(atan(py/px)), cos(atan(py/px)), 0.0},
					{0.0,  0.0, 0.0, 0.0,  0.0, 1.0}
	};
	test = arma::abs(obj_t3.GetTransformationMatrix() - expected)<1E-6;
	CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(
			"We expect the binary matrix to have the element 1 at each position",
			36.0,
			sum(sum(test,1)),
			0
	);

	// only the relative position of Point matters
	end =  PointManager::GetInstance().GetPoint(px+1,py+1,pz+1);
	start = PointManager::GetInstance().GetPoint(1.0,1.0,1.0);
	InternalTrussElement obj_t4 = InternalTrussElement(start,end,cross_sec,BASIC);
	test = arma::abs(obj_t4.GetTransformationMatrix() - expected)<1E-6;
	CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(
			"We expect the binary matrix to have the element 1 at each position",
			36.0,
			sum(sum(test,1)),
			0
	);
}

/*
 * truss_stiffness test
 */
void InternalStructuralElementObjectTest::truss_stiffness_test(){
	Point* start = PointManager::GetInstance().GetPoint(0.0, 0.0, 0.0);
	Point* end = PointManager::GetInstance().GetPoint(1.0, 0.0, 0.0);
  float A = 2300E-6; // in m^2
	arma::umat test;

	InternalTrussElement obj_t = InternalTrussElement(start,end,A,BASIC);
	float coef = (float) ( obj_t.GetCrossSection()*obj_t.GetYoungModulus()/obj_t.GetLength() );
	StiffnessMatrixType expected = {
		{coef, 0.0, 0.0, -coef, 0.0, 0.0},   // U0
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // V0
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // W0
		{-coef, 0.0, 0.0, coef, 0.0, 0.0},   // U1
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // V1
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // W1
	};

	test = arma::abs(obj_t.GetLocalStiffnessMatrix() - expected)<1E-6;
	CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(
			"We expect the binary matrix to have the element 1 at each position",
			36.0,
			sum(sum(test,1)),
			0
	);
}

/*
 * beam_transformation_test
 */
void InternalStructuralElementObjectTest::beam_transformation_test(){
	Point* start = PointManager::GetInstance().GetPoint(0.0, 0.0, 0.0);
	Point* end = PointManager::GetInstance().GetPoint(1.0, 0.0, 0.0);
  float A = 2300E-6; // in m^2
	arma::umat test;

	InternalBeamElement obj_b = InternalBeamElement(start,end,A,BASIC);
	TransformationMatrixType expected = arma::eye<TransformationMatrixType>(12,12);
	test = arma::abs(expected - obj_b.GetTransformationMatrix())<1E-6 ;
	//std::cout << obj_b.GetTransformationMatrix() << std::endl;
	CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(
			"We expect the BeamType with (0,0,0) and (1,1,1) equal to eye.",
			12*12,
			sum(sum(test,1)),
			0
	);
}

/*
 * beam_stiffness_test
 */
void InternalStructuralElementObjectTest::beam_stiffness_test(){
	Point* start = PointManager::GetInstance().GetPoint(0.0, 0.0, 0.0);
	Point* end = PointManager::GetInstance().GetPoint(2.2, 1.1, 3.3); // set complex coord to have a length != 0
  float a = 20; // in m^2, no reallistic number, just for have huge number to facilitate test
	arma::umat test;

	InternalBeamElement obj_b = InternalBeamElement(start,end,a,BASIC);
	float A = obj_b.GetCrossSection(),
			  E = obj_b.GetYoungModulus(),
				L = obj_b.GetLength(),
				G = 0.0,
				J = 0.0;
	StiffnessMatrixType expected = {
		{A*E/L,0.0,0.0, 0.0,0.0,0.0, -A*E/L,0.0,0.0, 0.0,0.0,0.0},
		{0.0,12*E/pow(L,(float)3.0),0.0, 0.0,0.0,6*E/pow(L,(float)2.0), 0.0,-12*E/pow(L,(float)3.0),0.0, 0.0,0.0,6*E/pow(L,(float)2)},
		{0.0,0.0,12*E/pow(L,(float)3), 0.0,-6*E/pow(L,(float)2),0.0, 0.0,0.0,-12*E/pow(L,(float)3), 0.0,-6*E/pow(L,(float)2),0.0},

		{0.0,0.0,0.0, G*J/L,0.0,0.0, 0.0,0.0,0.0, -G*J/L,0.0,0.0},
		{0.0,0.0,-6*E/pow(L,(float)2), 0.0,4*E/L,0.0, 0.0,0.0,6*E/pow(L,(float)2), 0.0,2*E/L,0.0},
		{0.0,6*E/pow(L,(float)2),0.0, 0.0,0.0,4*E/L, 0.0,-6*E/pow(L,(float)2),0.0, 0.0,0.0,2*E/L},

		{-A*E/L,0.0,0.0, 0.0,0.0,0.0, A*E/L,0.0,0.0, 0.0,0.0,0.0},
		{0.0,-12*E/pow(L,(float)3),0.0, 0.0,0.0,-6*E/pow(L,(float)2), 0.0,12*E/pow(L,(float)3),0.0, 0.0,0.0,-6*E/pow(L,(float)2)},
		{0.0,0.0,-12*E/pow(L,(float)3), 0.0,6*E/pow(L,(float)2),0.0, 0.0,0.0,12*E/pow(L,(float)3), 0.0,6*E/pow(L,(float)2),0.0},

		{0.0,0.0,0.0, -G*J/L,0.0,0.0, 0.0,0.0,0.0, G*J/L,0.0,0.0},
		{0.0,0.0,-6*E/pow(L,(float)2), 0.0,2*E/L,0.0, 0.0,0.0,6*E/pow(L,(float)2), 0.0,4*E/L,0.0},
		{0.0,6*E/pow(L,(float)2),0.0, 0.0,0.0,2*E/L, 0.0,-6*E/pow(L,(float)2),0.0, 0.0,0.0,4*E/L},
	};

	test = (arma::abs(expected - obj_b.GetLocalStiffnessMatrix()))<1E-6 ;
	//std::cout << expected << std::endl;
	//std::cout << "*******************" << std::endl;
	//std::cout << obj_b.GetLocalStiffnessMatrix() << std::endl;
	//std::cout << "*******************" << std::endl;
	//std::cout << test << std::endl;
	CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(
			"We expect the default stiffness matrix",
			12*12,
			sum(sum(test,1)),
			0
	);
}
