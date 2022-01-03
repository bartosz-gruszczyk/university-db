#include "gtest/gtest.h"
#include "errors.hpp"
#include "database.hpp"


// // TEST(DataBaseAddStudentCorrect, shouldAddStudentCorrectly) {
// TEST(DataBaseAddStudentTests, shouldAddStudentCorrectly) {
//     DataBase cut;
//     auto result = cut.addStudent("Bartek", "Gruszczyk", "12345634129", Address("03-333", "Warszawa", "Kwiatowa 666"), Sex::Male, 1);
//     ASSERT_EQ(result, ErrorCode::Ok);
// }

// // TEST(DataBaseAddStudentInvalidPesel, shouldReturnInvalidPesel) {
// TEST(DataBaseAddStudentTests, shouldReturnInvalidPesel) {
//     DataBase cut;
//     auto result = cut.addStudent("John", "Doe", "1234", Address("03-333", "Warszawa", "Kwiatowa 666"), Sex::Male, 1);
//     ASSERT_EQ(result, ErrorCode::InvalidPesel);
// }

class DataBaseAddStudentFixture : public ::testing::Test {
public:
    DataBase cut;
};

TEST_F(DataBaseAddStudentFixture, shouldAddStudentCorrectly) {
    const std::string firstName = "Bartek";
    const std::string lastName = "Gruszczyk";
    const std::string pesel = "12345634129";
    const Address address("03-333", "Warszawa", "Kwiatowa 666");
    const Sex sex = Sex::Male;
    const size_t indexNumber = 1;

    auto sizeBeforeAdding = cut.data().size();
    auto result = cut.addStudent(firstName, lastName, pesel, address, sex, indexNumber);

    ASSERT_EQ(result, ErrorCode::Ok);
    EXPECT_EQ(cut.data().size(), sizeBeforeAdding + 1);
    EXPECT_EQ(cut.data()[sizeBeforeAdding]->getFirstName(), firstName);
    EXPECT_EQ(cut.data()[sizeBeforeAdding]->getLastName(), lastName);
    EXPECT_EQ(cut.data()[sizeBeforeAdding]->getPesel(), pesel);
    EXPECT_EQ(cut.data()[sizeBeforeAdding]->address(), address); // sprawdzic czy operator porownania dziala
    EXPECT_EQ(cut.data()[sizeBeforeAdding]->getSex(), sex);
    EXPECT_EQ(cut.data()[sizeBeforeAdding]->getIndexNumber(), indexNumber);
    // EXPECT_EQ(cut.data().->getFirstName(.}
}

TEST_F(DataBaseAddStudentFixture, shouldReturnInvalidPesel) {
    auto result = cut.addStudent("John", "Doe", "1234", Address("03-333", "Warszawa", "Kwiatowa 666"), Sex::Male, 1);
    EXPECT_EQ(result, ErrorCode::InvalidPesel);

    // EXPECT_EQ(result, ErrorCode::InvalidPesel);
}