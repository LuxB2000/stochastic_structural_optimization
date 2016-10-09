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

/*
 * private function
 */
void InternalStructuralElementObjectTest::copy_R_in_T(TransformationMatrixType R, TransformationMatrixType* T) {

	(*T)(0,0) = (*T)(3,3) = (*T)(6,6) = (*T)(9,9) = R(0,0);
	(*T)(0,1) = (*T)(3,4) = (*T)(6,7) = (*T)(9,10) = R(0,1);
	(*T)(0,2) = (*T)(3,5) = (*T)(6,8) = (*T)(9,11) = R(0,2);
	(*T)(1,0) = (*T)(4,3) = (*T)(7,6) = (*T)(10,9) = R(1,0);
	(*T)(1,1) = (*T)(4,4) = (*T)(7,7) = (*T)(10,10) = R(1,1);
	(*T)(1,2) = (*T)(4,5) = (*T)(7,8) = (*T)(10,11) = R(1,2);
	(*T)(2,0) = (*T)(5,3) = (*T)(8,6) = (*T)(11,9) = R(2,0);
	(*T)(2,1) = (*T)(5,4) = (*T)(8,7) = (*T)(11,10) = R(2,1);
	(*T)(2,2) = (*T)(5,5) = (*T)(8,8) = (*T)(11,11) = R(2,2);
}
void InternalStructuralElementObjectTest::copy_R_in_T_test(){
	arma::umat test;
	TransformationMatrixType R = {
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1}
	};
	TransformationMatrixType T = TransformationMatrixType(12,12,arma::fill::zeros);
	TransformationMatrixType expected_eye = arma::eye<TransformationMatrixType>(12,12);
	copy_R_in_T(R,&T);
	//std::cout << T << std::endl;
	test = (T == expected_eye);
	CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(
			"We expect a 12x12 eye matrix",
			12*12,
			sum(sum(test,1)),
			0
	);

}

/*
 * basic_test
 */
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
	//std::cout << obj_t.GetTransformationMatrix() << std::endl;
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
	//std::cout << obj_t2.GetTransformationMatrix() << std::endl;
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

	// test with z != 0
	pz = 2.0;
	end =  PointManager::GetInstance().GetPoint(px,py,pz);
	InternalTrussElement obj_t5 = InternalTrussElement(start,end,cross_sec,BASIC);
	expected = {
		{0.5071, -0.8575, -0.087, 0.0, 0.0, 0.0},
		{0.8452,  0.5145, -0.145, 0.0, 0.0, 0.0},
		{0.1690,  0,       0.986, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.5071, -0.8575, -0.087},
		{0.0, 0.0, 0.0, 0.8452,  0.5145, -0.145},
		{0.0, 0.0, 0.0, 0.1690,  0,       0.986},
	};
	//std::cout << obj_t5.GetTransformationMatrix() << std::endl;
	test = arma::abs(obj_t5.GetTransformationMatrix() - expected)<1E-3;
	CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(
			"We expect the correct transformation matrix with z coord != 0",
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
	TransformationMatrixType expected_eye = arma::eye<TransformationMatrixType>(12,12);
	test = arma::abs(expected_eye - obj_b.GetTransformationMatrix())<1E-6 ;
	//std::cout << obj_b.GetTransformationMatrix() << std::endl;
	CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(
			"We expect the BeamType with (0,0,0) and (1,1,1) equal to eye.",
			12*12,
			sum(sum(test,1)),
			0
	);


	// vertical beam
	end = PointManager::GetInstance().GetPoint(0.0, 1.0, 0.0);
	InternalBeamElement obj_b2 = InternalBeamElement(start,end,A,BASIC, 0.0);
	// transformation matrix is generated by a 3x3 sub-matrix R
	TransformationMatrixType expected_R ={ 
		{ 0.0, 1.0, 0.0},
		{ 0.0, 0.0, 0.0},
		{ 0.0, 0.0, 0.0}
	};
	TransformationMatrixType expected = TransformationMatrixType(12,12,arma::fill::zeros);
	copy_R_in_T(expected_R, &expected);
	test = arma::abs(expected - obj_b2.GetTransformationMatrix())<1E-6;
	//std::cout << obj_b2.GetTransformationMatrix() << std::endl;
	CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(
			"We expect a vertical beam with only Cy!=0.",
			12*12,
			sum(sum(test,1)),
			0
	);

	// general formulation
	end = PointManager::GetInstance().GetPoint(3.0,4.0,1.0);
	float alpha = 10.0;
	InternalBeamElement obj_b3 = InternalBeamElement(start,end,A,BASIC, alpha);
	float L = sqrt( pow(end->x-start->x,2)+ pow(end->y-start->y,2)+ pow(end->z-start->z,2) );
	float Cx = (end->x - start->x)/L;
	float Cy = (end->y - start->y)/L;
	float Cz = (end->z - start->z)/L;
	float s = sin(alpha);
	float c = cos(alpha);
	float Cxz = sqrt(pow(Cx,2) + pow(Cz,2)) + 1E-8; // to prevent division by 0
	expected_R = {
			{Cx, Cy, Cz},
			{(-Cx*Cy*c-Cz*s)/Cxz, Cxz*c, (-Cy*Cz*c+Cx*s)/Cxz},
			{(Cx*Cy*s -Cz*c)/Cxz, -Cxz*s,(Cy*Cz*s+Cx*c)/Cxz}
		};
	copy_R_in_T(expected_R,&expected);
	test = arma::abs(expected - obj_b3.GetTransformationMatrix())<1E-6;
	CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(
			"We expect to match the general formulation",
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

void InternalStructuralElementObjectTest::beam_stiffness_file_test(void){
	float x1 = 1.0, y1 = 2.0, z1 = 3.0,
				x2 = 2.0, y2 = 1.0, z2 = 5.0;
	float cross_sect = 23E-4; // in m^2
	Material m = BASIC;
	arma::umat test;
	Point *start = PointManager::GetInstance().GetPoint(x1,y1,z1),
				*end   = PointManager::GetInstance().GetPoint(x2,y2,z2);
	InternalBeamElement obj_b = InternalBeamElement(start,end,cross_sect,BASIC);
	TransformationMatrixType expected_C;
	bool check = expected_C.load("../tests/data/C_transformed_beam.mat",arma::raw_ascii);//TODO: better path
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
			"File C_transformed_beam.mat can't be read.",
			true,
			check
	);

	test = arma::abs(expected_C - obj_b.GetTransformationMatrix())<1E-3;
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect the stiffness matrix for a randomly oriented BeamBarElement",
		144,
		(int)sum(sum(test,1))
	);

}
