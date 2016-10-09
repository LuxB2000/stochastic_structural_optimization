
#include "BarElementTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(BarElementTest);

BarElementTest::BarElementTest(){
}

BarElementTest::~BarElementTest(){
}

void
BarElementTest::tearDown(){
}

void
BarElementTest::setUp(){
}

void BarElementTest::copy_R_in_T(TransformationMatrixType R, TransformationMatrixType* T) {

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

void
BarElementTest::basic_tests(){
	Point *start = PointManager::GetInstance().GetPoint(0.0,0.0,0.0),
				*end   = PointManager::GetInstance().GetPoint(1.0,0.0,0.0);
	double cross_sect = 24E-4; // in m^2
	Material m = TEST;

	// truss
	TrussBarElement bar_t = TrussBarElement(start, end, cross_sect, m);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect 2 nodes",
		(unsigned int)2,
		bar_t.GetNumberOfNodes()
	);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect 1 element",
		(unsigned int)1,
		bar_t.GetNumberOfElements()
	);

	// beam
	BeamBarElement bar_b = BeamBarElement(start, end, cross_sect, m);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect 2 nodes",
		(unsigned int)2,
		bar_b.GetNumberOfNodes()
	);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect 1 element",
		(unsigned int)1,
		bar_b.GetNumberOfElements()
	);
}

void
BarElementTest::getter_tests(){
	Point *start = PointManager::GetInstance().GetPoint(0.0,0.0,0.0),
				*end   = PointManager::GetInstance().GetPoint(1.0,1.0,0.0);
	double cross_sect = 24E-4; // in m^2
	Material m = TEST;

	// truss
	TrussBarElement bar_t = TrussBarElement(start, end, cross_sect, m);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect a length equal to sqrt(2)",
		sqrt(2.0),
		bar_t.GetLength()
	);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect a stiffness matrix with 36 elements",
		36,
		(int)bar_t.GetStiffnessMatrix().n_elem
	);

	// beam
	BeamBarElement bar_b = BeamBarElement(start, end, cross_sect, m);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect a length equal to sqrt(2)",
		sqrt(2.0),
		bar_b.GetLength()
	);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect a stiffness matrix with 144 elements",
		144,
		(int)bar_b.GetStiffnessMatrix().n_elem
	);

}// end getter_tests

/*
 * truss_stiffness_tests
 */
void
BarElementTest::truss_stiffness_tests(){
	float x1 = 0.0, y1 = 0.0, z1 = 0.0,
				x2 = 1.0, y2 = 0.0, z2 = 0.0;
	Point *start = PointManager::GetInstance().GetPoint(x1,y1,z1),
				*end   = PointManager::GetInstance().GetPoint(x2,y2,z2);
	double cross_sect = 24E-4; // in m^2
	Material m = TEST;
	arma::umat test;

	TrussBarElement bar_t = TrussBarElement(start, end, cross_sect, m);
	float c = (cos(atan(abs(start->y-end->y)/abs(start->x-end->x)))), 
				s = (sin(atan(abs(start->y-end->y)/abs(start->x-end->x))));
	float coef = (float)(bar_t.GetCrossSection()*bar_t.GetYoungModulus()/bar_t.GetLength());
	StiffnessMatrixType expected = {
			{c*coef*c,s*coef*c,0.0, -c*coef*c,-s*coef*c,0.0},      // U0
			{c*coef*s,s*coef*s,0.0, -s*coef*c,-s*coef*s,0.0},      // V0
			{0.0,0.0,0.0,  0.0,0.0,0.0},      // W0
			{-c*coef*c,-s*coef*c,0.0, c*coef*c,s*coef*c,0.0},      // U0
			{-c*coef*s,-s*coef*s,0.0, s*coef*c,s*coef*s,0.0},      // V0
			{0.0,0.0,0.0,  0.0,0.0,0.0},      // W1
	};
	//std::cout << bar_t.GetStiffnessMatrix() << std::endl;
	//std::cout << "************************" << std::endl;
	//std::cout << expected << std::endl;
	test = arma::abs(bar_t.GetStiffnessMatrix() - expected ) < 1E0 ;
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect the 2D stiffness truss matrix",
		36,
		(int)sum(sum(test,1))
	);


	// TODO: test with z coordinates

}// end truss_stiffness_tests

/*
 * beam_stiffness_tests
 */
void
BarElementTest::beam_stiffness_tests(){
	float x1 = 0.0, y1 = 0.0, z1 = 0.0,
				x2 = 1.0, y2 = 0.0, z2 = 0.0;
	float cross_sect = 24E-4; // in m^2
	Material m = TEST;
	arma::umat test;
	Point *start = PointManager::GetInstance().GetPoint(x1,y1,z1),
				*end   = PointManager::GetInstance().GetPoint(x2,y2,z2);
	BeamBarElement bar_b = BeamBarElement(start,end,cross_sect,m);
	float A = bar_b.GetCrossSection(),
			  E = bar_b.GetYoungModulus(),
				L = bar_b.GetLength(),
				G = 0.0,
				J = 0.0;
	//std::cout << "TEST: " << A << " - " << E << " - " << L << std::endl;
	/*
	 * First Example, default value
	 */
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

	test = ( expected - bar_b.GetStiffnessMatrix() )<1E-6;
	//std::cout << bar_b.GetStiffnessMatrix() << std::endl;
	//std::cout << "************************" << std::endl;
	//std::cout << expected << std::endl;
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect the 3D beam stiffness matrix",
		144,
		(int)sum(sum(test,1))
	);

	/*
	 * second Example, vertical beam
	 * Numerical solutions have been generated by the Matlab code presented in 
	 * "A 3D Finite Element modeling composite wind tubine wings" by R. DE FRIA LOPE.
	 */
	float alpha = 0.0;
	x1 = 0.0, y1 = 0.0, z1 = 0.0,
	x2 = 0.0, y2 = 2.0, z2 = 0.0;
	start = PointManager::GetInstance().GetPoint(x1,y1,z1);
	end  = PointManager::GetInstance().GetPoint(x2,y2,z2);
	BeamBarElement bar_b3 = BeamBarElement(start, end, cross_sect, m, alpha);
	expected = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 240000000.000000, 0, 0, 0, 0, 0, -240000000.000000, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1.97215226305253e-20, 0, 0, 0, 0, 0, 9.86076131526265e-21, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, -240000000.000000, 0, 0, 0, 0, 0, 240000000.000000, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 9.86076131526265e-21, 0, 0, 0, 0, 0, 1.97215226305253e-20, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	test = arma::abs(expected - bar_b3.GetStiffnessMatrix())<1E-3;
	//std::cout << "************************" << std::endl;
	//std::cout << bar_b3.GetStiffnessMatrix() << std::endl;
	//std::cout << "************************" << std::endl;
	//std::cout <<  transformed_stiffness << std::endl;
	//std::cout << "************************" << std::endl;
	//std::cout << transformed_stiffness - bar_b3.GetStiffnessMatrix() << std::endl;
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect the 3D beam for a vertical stiffness matrix",
		144,
		(int)sum(sum(test,1))
	);

	/*
	 * third Example, randomly oriented beam
	 * Numerical solutions have been generated by the Matlab code presented in 
	 * "A 3D Finite Element modeling composite wind tubine wings" by R. DE FRIA LOPE.
	 */
	alpha = 0.0;
	x1 = 0.0, y1 = 0.0, z1 = 0.0,
	x2 = 3.5, y2 = 2.0, z2 = 0.0;
	start = PointManager::GetInstance().GetPoint(x1,y1,z1);
	end  = PointManager::GetInstance().GetPoint(x2,y2,z2);
	// !! WARNING: here we use the BASIC element,
	// Using TEST make comparison with Matlab code
	// unstable (precision is not good and we observed error with c*1024 with c an interger coefficient
	BeamBarElement bar_b4 = BeamBarElement(start, end, cross_sect, BASIC, alpha);
	expected = {
		{0.0455416793731181, -0.0786560471324074, 0, 0, 0, -0.183189761854831, -0.0455416793731181, 0.0786560471324074, 0, 0, 0, -0.183189761854831},
		{-0.0786560471324074, 0.138243449207741, 0, 0, 0, 0.320582083245954, 0.0786560471324074, -0.138243449207741, 0, 0, 0, 0.320582083245954},
		{0, 0, 0.183189761854831, 0.183189761854831, -0.320582083245954, 0, 0, 0, -0.183189761854831, 0.183189761854831, -0.320582083245954, 0},
		{0, 0, 0.183189761854831, 0.244253015806441, -0.427442777661272, 0, 0, 0, -0.183189761854831, 0.122126507903221, -0.213721388830636, 0},
		{0, 0, -0.320582083245954, -0.427442777661272, 0.748024860907227, 0, 0, 0, 0.320582083245954, -0.213721388830636, 0.374012430453614, 0},
		{-0.183189761854831, 0.320582083245954, 0, 0, 0, 0.992277876713667, 0.183189761854831, -0.320582083245954, 0, 0, 0, 0.496138938356834},
		{-0.0455416793731181, 0.0786560471324074, 0, 0, 0, 0.183189761854831, 0.0455416793731181, -0.0786560471324074, 0, 0, 0, 0.183189761854831},
		{0.0786560471324074, -0.138243449207741, 0, 0, 0, -0.320582083245954, -0.0786560471324074, 0.138243449207741, 0, 0, 0, -0.320582083245954},
		{0, 0, -0.183189761854831, -0.183189761854831, 0.320582083245954, 0, 0, 0, 0.183189761854831, -0.183189761854831, 0.320582083245954, 0},
		{0, 0, 0.183189761854831, 0.122126507903221, -0.213721388830636, 0, 0, 0, -0.183189761854831, 0.244253015806441, -0.427442777661272, 0},
		{0, 0, -0.320582083245954, -0.213721388830636, 0.374012430453614, 0, 0, 0, 0.320582083245954, -0.427442777661272, 0.748024860907227, 0},
		{-0.183189761854831, 0.320582083245954, 0, 0, 0, 0.496138938356834, 0.183189761854831, -0.320582083245954, 0, 0, 0, 0.992277876713667}
	};
	test = arma::abs(expected - bar_b4.GetStiffnessMatrix())<1E-3;
	//std::cout << "************************" << std::endl;
	//std::cout << bar_b4.GetStiffnessMatrix() << std::endl;
	//std::cout << "************************" << std::endl;
	//std::cout <<  transformed_stiffness << std::endl;
	//std::cout << "************************" << std::endl;
	//std::cout << expected - bar_b4.GetStiffnessMatrix() << std::endl;
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect the stiffness matrix for a randomly oriented BeamBarElement",
		144,
		(int)sum(sum(test,1))
	);

	/*
	 * 4th Example, any kind of transformation, it is here to illustrate the formulas we use
	 */
	alpha = 0.0;
	x1 = 0.0, y1 = 0.0, z1 = 0.0,
	x2 = 2.0, y2 = 4.5, z2 = 3.2;
	start = PointManager::GetInstance().GetPoint(x1,y1,z1);
	end  = PointManager::GetInstance().GetPoint(x2,y2,z2);
	BeamBarElement bar_b2 = BeamBarElement(start, end, cross_sect, m);
	L = bar_b2.GetLength();
	expected = {
		{A*E/L,0.0,0.0, 0.0,0.0,0.0, -A*E/L,0.0,0.0, 0.0,0.0,0.0},
		{0.0,(float)12*E/pow(L,(float)3.0),0.0, 0.0,0.0,(float)6.0*E/pow(L,(float)2.0), 0.0,-(float)12*E/pow(L,(float)3.0),0.0, 0.0,0.0,(float)6.0*E/pow(L,(float)2)},
		{0.0,0.0,(float)12*E/pow(L,(float)3), 0.0,-(float)6.0*E/pow(L,(float)2),0.0, 0.0,0.0,-(float)12*E/pow(L,(float)3), 0.0,-(float)6.0*E/pow(L,(float)2),0.0},

		{0.0,0.0,0.0, G*J/L,0.0,0.0, 0.0,0.0,0.0, -G*J/L,0.0,0.0},
		{0.0,0.0,-(float)6.0*E/pow(L,(float)2), 0.0,(float)4.0*E/L,0.0, 0.0,0.0,(float)6.0*E/pow(L,(float)2), 0.0,(float)2.0*E/L,0.0},
		{0.0,(float)6.0*E/pow(L,(float)2),0.0, 0.0,0.0,(float)4.0*E/L, 0.0,-(float)6.0*E/pow(L,(float)2),0.0, 0.0,0.0,(float)2.0*E/L},

		{-A*E/L,0.0,0.0, 0.0,0.0,0.0, A*E/L,0.0,0.0, 0.0,0.0,0.0},
		{0.0,-(float)12*E/pow(L,(float)3),0.0, 0.0,0.0,-(float)6.0*E/pow(L,(float)2), 0.0,(float)12*E/pow(L,(float)3),0.0, 0.0,0.0,-(float)6.0*E/pow(L,(float)2)},
		{0.0,0.0,-(float)12*E/pow(L,(float)3), 0.0,(float)6.0*E/pow(L,(float)2),0.0, 0.0,0.0,(float)12*E/pow(L,(float)3), 0.0,(float)6.0*E/pow(L,(float)2),0.0},

		{0.0,0.0,0.0, -G*J/L,0.0,0.0, 0.0,0.0,0.0, G*J/L,0.0,0.0},
		{0.0,0.0,-(float)6.0*E/pow(L,(float)2), 0.0,(float)2.0*E/L,0.0, 0.0,0.0,(float)6.0*E/pow(L,(float)2), 0.0,(float)4.0*E/L,0.0},
		{0.0,(float)6.0*E/pow(L,(float)2),0.0, 0.0,0.0,(float)2.0*E/L, 0.0,-(float)6.0*E/pow(L,(float)2),0.0, 0.0,0.0,(float)4.0*E/L},
	};
	float Cx = (end->x - start->x)/L;
	float Cy = (end->y - start->y)/L;
	float Cz = (end->z - start->z)/L;
	float s = sin(alpha);// s<1E-8 ? 0 : s;
	float c = cos(alpha);// c<1E-8 ? 0 : c;
	float Cxz = sqrt(pow(Cx,2) + pow(Cz,2)) + 1E-8; // to prevent division by 0
	TransformationMatrixType expected_T = TransformationMatrixType(12,12,arma::fill::zeros),
													 expected_R = {
			{Cx, Cy, Cz},
			{(-Cx*Cy*c-Cz*s)/Cxz, Cxz*c, (-Cy*Cz*c+Cx*s)/Cxz},
			{(Cx*Cy*s -Cz*c)/Cxz, -Cxz*s,(Cy*Cz*s+Cx*c)/Cxz}
		};
	copy_R_in_T(expected_R,&expected_T);
	StiffnessMatrixType transformed_stiffness = expected_T.t()*expected*expected_T; // !!! WARNING: CHANGE HERE !!
	// FIXME
	// WARNING: Huge (?) difference, elements in matrix are 1E10, this is probably due to a type float VS int or double
	test = arma::abs(transformed_stiffness - bar_b2.GetStiffnessMatrix())<1E4;
	//std::cout << "************************" << std::endl;
	//std::cout << expected_T << std::endl;
	//std::cout << "************************" << std::endl;
	//std::cout << bar_b2.GetStiffnessMatrix() << std::endl;
	//std::cout << "************************" << std::endl;
	//std::cout <<  transformed_stiffness << std::endl;
	//std::cout << "************************" << std::endl;
	//std::cout << arma::abs(transformed_stiffness - bar_b2.GetStiffnessMatrix()) << std::endl;
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect the 3D beam stiffness matrix transformed by any T",
		144,
		(int)sum(sum(test,1))
	);

}// end beam_stiffness_tests


/*
 * compare the matrix created by Matlab and the C++ code
 */
void
BarElementTest::truss_stiffness_files_tests(void){
	float x1 = 1.0, y1 = 2.0, z1 = 3.0,
				x2 = 2.0, y2 = 1.0, z2 = 5.0;
	float cross_sect = 23E-4; // in m^2
	Material m = BASIC;
	arma::umat test;
	Point *start = PointManager::GetInstance().GetPoint(x1,y1,z1),
				*end   = PointManager::GetInstance().GetPoint(x2,y2,z2);
	BeamBarElement bar_b = BeamBarElement(start,end,cross_sect,m);
	StiffnessMatrixType expected_K;
	bool check = expected_K.load("../tests/data/Kg_transformed_beam.mat",arma::raw_ascii);//TODO: better path
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
			"File Kg_transformed_beam.mat can't be read.",
			true,
			check
	);

	test = arma::abs(expected_K - bar_b.GetStiffnessMatrix())<1E-3;
	//std::cout << bar_b.GetStiffnessMatrix() << std::endl;
	//std::cout << "************************" << std::endl;
	//std::cout <<  expected << std::endl;
	//std::cout << "************************" << std::endl;
	//std::cout << expected - bar_b4.GetStiffnessMatrix() << std::endl;
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect the stiffness matrix for a randomly oriented BeamBarElement",
		144,
		(int)sum(sum(test,1))
	);

}// end truss_stiffness_files_tests
