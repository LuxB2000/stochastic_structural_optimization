//
// Created by plumat on 4/13/16.
//

#include "../headers/GramSchmidtProcessTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(GramSchmidtProcessTest);

GramSchmidtProcessTest::GramSchmidtProcessTest() {

}

GramSchmidtProcessTest::~GramSchmidtProcessTest() {

}

void GramSchmidtProcessTest::tearDown() {
    if(m_gsp) delete m_gsp;
}

void GramSchmidtProcessTest::setUp() {
    m_gsp = new GramSchmidtProcess();
}

void GramSchmidtProcessTest::projection_tests() {
    GramSchmidtProcess::VectorType v = {1,0,0}, u = {1,0,0}, p={0,0,0}, expected={0.0,0.0,0.0};
    arma::uvec test={0,0,0};

    m_gsp->Proj(&u,&v,&p); // compute the projection of v on u
    test = (p==v);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The projection should return the original vector",3.0, static_cast<double>(sum(test)));

    v={-2,3,4}; u={1,1,1};
    m_gsp->Proj(&u,&v,&p);
    expected = {(double)5/3,(double)5/3,(double)5/3};
    //cout << p << endl;
    for(unsigned int i=0; i<expected.n_elem; i++){
        CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect a known vector",
                                 expected(i), p(i), 1E-3 );
    }
}

void GramSchmidtProcessTest::process_tests(void) {
    GramSchmidtProcess::VectorType v = {1.0,0.0,0.0}, e1={0.0,0.0,0.0}, e2={0.0,0.0,0.0}, e3={0.0,0.0,0.0};
    GramSchmidtProcess::VectorType s1, s2, s3;
    arma::uvec t1, t2, t3;

    s1 = {1.0, 0.0, 0.0}; s2 = {0.0, 1.0, 0.0}; s3 = {0.0, 0.0, 1.0};
    m_gsp->ComputeOrthonormalBasisFromVector(&v,&e1,&e2,&e3); // should be {1,0,0}, {0,1,0} and {
    t1 = (e1==s1); t2 = (e2==s2); t3=(e3==s3);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect the default basis", 3.0, (double)sum(t1));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect the default basis", 3.0, (double)sum(t2));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect the default basis", 3.0, (double)sum(t3));

    v = {0.0,1.0,0.0};
    s1 = {0.0, 1.0, 0.0}; s2 = {-1.0, 0.0, 0.0}; s3 = {0.0, 0.0, 1.0};
    m_gsp->ComputeOrthonormalBasisFromVector(&v,&e1,&e2,&e3);
    t1 = (e1==s1); t2 = (e2==s2); t3=(e3==s3);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect {0,1,0}", 3.0, (double)sum(t1));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect {-1,0,0}", 3.0, (double)sum(t2));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect {0,0,1}", 3.0, (double)sum(t3));

    v = {0.0,0.0,1.0};
    s1 = {0.0, 0.0, 1.0}; s2 = {0.0, -1.0, 0.0}; s3 = {1.0, 0.0, 0.0};
    m_gsp->ComputeOrthonormalBasisFromVector(&v,&e1,&e2,&e3);
    t1 = (e1==s1); t2 = (e2==s2); t3=(e3==s3);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect {0,0,1}", 3.0, (double)sum(t1));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect {0,-1,0}",3.0, (double)sum(t2));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect {1,0,0}",3.0, (double)sum(t3));

    v = {1.0,1.0,1.0};
    s1 = {1.0/sqrt(3), 1.0/sqrt(3), 1.0/sqrt(3)}; s2 = {-1.0/sqrt(2), 1.0/sqrt(2), 0.0};
    s3 = {-1+1/sqrt(2),-1/sqrt(2),1};
    s3 = s3 / norm(s3);
    m_gsp->ComputeOrthonormalBasisFromVector(&v,&e1,&e2,&e3);
    t1 = (e1==s1); t2 = (e2==s2); t3=(e3==s3);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect {1/sqrt(3),1/sqrt(3),1/sqrt(3)}", 3.0, (double)sum(t1));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect {-1/sqrt(2),1/sqrt(2),0}", 3.0, (double)sum(t2));
    //CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect {1,0,0}", 3.0, (double)sum(t3)); //TODO: find the good theoretical value

    v = {-1.0,1.0,0.0};
    m_gsp->ComputeOrthonormalBasisFromVector(&v,&e1,&e2,&e3);
}
