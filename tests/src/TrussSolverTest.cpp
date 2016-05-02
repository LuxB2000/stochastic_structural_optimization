

#include "../headers/TrussSolverTest.h"

#include "Truss.h"
#include "StiffnessMatrixBuilder.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TrussSolverTest);

TrussSolverTest::TrussSolverTest(){

}

TrussSolverTest::~TrussSolverTest(){

}


void TrussSolverTest::setUp(){

}

void TrussSolverTest::tearDown(){

}

void TrussSolverTest::basic_tests(){
    TrussSolver solver = TrussSolver();
}

void TrussSolverTest::compute_all_tests() {

    // Try to match examples developed in the book:
    // "Introduction to Finite Element Analysis Using Matlab and Abaqus, Amar Khennane, 2013", chap 1, page 9-19

    const unsigned int n_dof = 3, n_pt = 3;

    // configure the space to solve  (problem is assumed to be planar)
    // ^ y
    // |
    //  -->x
    //
    //         2 --> f2x
    //  t3  /  |
    //     /   | t2
    //    0 ---1
    //      t1
    // support at
    // p0: support forces displacement dx=dy=0 -> presence of two forces Rx,Ry
    // p1: support forces displacement dy=0=0 -> presence of one force Ry
    // p3: no support -> no force -> 2 displacement possibles: dx,dy BUT one external force f3x=12kN

    // problem inputs
    float A = 2300; // section in mm^2
    float fx2 = 12000; //external force, in N
    float x0=0.0, y0=0.0, z0=0.0, x1=4000.0, y1=0.0, z1=0.0, x2=4000.0, y2=6000.0, z2=0.0; // coord in millimeters

    // defining the points
    Point p0 = Point(x0,y0,z0), p1 = Point(x1,y1,z1), p2 = Point(x2,y2,z2);

    // build the trusses
    Truss t0 = Truss(&p0,&p1,A,Truss::TEST);
    Truss t1 = Truss(&p1,&p2,A,Truss::TEST);
    Truss t2 = Truss(&p0,&p2,A,Truss::TEST);

    // build the stiffness matrix
    StiffnessMatrixBuilder stiffnessMatrixBuilder = StiffnessMatrixBuilder(n_dof*n_pt);
    stiffnessMatrixBuilder.Build(t0.GetLocalStiffnessMatrixPointer(),t0.GetLocalTransformationMatrixPointer(),0,1);
    stiffnessMatrixBuilder.Build(t1.GetLocalStiffnessMatrixPointer(),t1.GetLocalTransformationMatrixPointer(),1,2);
    stiffnessMatrixBuilder.Build(t2.GetLocalStiffnessMatrixPointer(),t2.GetLocalTransformationMatrixPointer(),0,2);

    // build the global force vector, in format (fx0,fy0,fz0,...,fxN,fyN,fzN)
    TrussSolver::ForceVectorType f = TrussSolver::ForceVectorType(n_dof*n_pt,arma::fill::zeros);
    // only one external force: fx2
    f(6)=fx2;

    // Boundary conditions
    TrussSolver::BoundaryConditionsVectorType bc = TrussSolver::BoundaryConditionsVectorType();
    bc.push_back({0,0}); // at joint 0, Rx=0
    bc.push_back({0,1}); // at joint 0, Ry=0
    bc.push_back({1,1}); // at joint 1, Ry=0

    // find the displacements
    TrussSolver::DisplacementVectorType disp = TrussSolver::DisplacementVectorType(),
        expected = {0,0,0, 0,0,0, 0.9635,(float)-0.2348,0};
    TrussSolver solver = TrussSolver();
    solver.ComputeDisplacements( &disp,stiffnessMatrixBuilder.GetStiffnessMatrixPointer(),&f,&bc);

   //std::cout << disp << std::endl;

    long l = expected.n_elem;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect to have the same size",l,(long)disp.n_elem);
    // dx0, dy0, dy1 can be ignored since there are joints
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect to find the same displacements dx1",expected(3),disp(3),1E-3); // dx1
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect to find the same displacements dx2",expected(6),disp(6),1E-3); // dx2
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect to find the same displacements dy2",expected(7),disp(7),1E-3); // dy2

    // no displacement along z axis
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect to find the same displacements dz0",expected(2),disp(2),1E-6); // dz0
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect to find the same displacements dz1",expected(5),disp(5),1E-6); // dz1
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect to find the same displacements dz2",expected(8),disp(8),1E-6); // dz2


    // find the forces
    solver.ComputeSupportReaction(&disp,stiffnessMatrixBuilder.GetStiffnessMatrixPointer(),&f,&bc);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect to have the same size",n_dof*n_pt,(unsigned int)f.n_elem);
    // want no change in fx3
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect to find the fx2 force",fx2,(float)f(6),1E-2); //Fx2
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect to find the Rx0 force",(float)-12E3,(float)f(0),1E-2); // Rx0
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect to find the Ry0 force",(float)-18E3,(float)f(1),1E-2); // Ry0
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect to find the Ry1 force",(float)18E3,(float)f(4),1E-2); // Ry1

}
