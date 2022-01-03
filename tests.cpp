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
    DataBaseAddStudentFixture() {
        cut.addStudent("Jan", "Kowalski", "78785285242", Address("99-111", "Krakow", "Stawowa 669"), Sex::Male, 5);
    }

    DataBase cut;
};

TEST_F(DataBaseAddStudentFixture, shouldAddStudentCorrectly) {
    const std::string firstName = "Marian";
    const std::string lastName = "Nowak";
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
}

TEST_F(DataBaseAddStudentFixture, shouldReturnInvalidPesel) {
    auto result = cut.addStudent("John", "Doe", "1234", Address("03-333", "Warszawa", "Kwiatowa 666"), Sex::Male, 1);
    EXPECT_EQ(result, ErrorCode::InvalidPesel);
    result = cut.addStudent("John", "Doe", "12345634122", Address("03-333", "Warszawa", "Kwiatowa 666"), Sex::Male, 1);
    EXPECT_EQ(result, ErrorCode::InvalidPesel);
}

TEST_F(DataBaseAddStudentFixture, shouldReturnPeselAlreadyExists) {
    auto result = cut.addStudent("Monika", "Kowalik", "78785285242", Address("99-111", " ", " "), Sex::Female, 9);
    EXPECT_EQ(result, ErrorCode::PeselAlreadyExists);
}

TEST_F(DataBaseAddStudentFixture, shouldReturnInvalidIndexNumber) {
    auto result = cut.addStudent("A", "B", "12345634129", Address("99-111", "C", "D"), Sex::Male, -32);
    EXPECT_EQ(result, ErrorCode::InvalidIndexNumber);
    result = cut.addStudent("E", "F", "78787878785", Address("99-111", "G", "H"), Sex::Male, DataBase::maxIndexNumber + 1);
    EXPECT_EQ(result, ErrorCode::InvalidIndexNumber);
}

TEST_F(DataBaseAddStudentFixture, shouldReturnIndexNumberAlreadyExists) {
    auto result = cut.addStudent("A", "B", "12345634129", Address("99-999", "C", "D"), Sex::Female, 5);
    EXPECT_EQ(result, ErrorCode::IndexNumberAlreadyExists);
}

class DataBaseRemovePersonFixture : public ::testing::Test {
public:
    DataBaseRemovePersonFixture() {
        cut.addStudent("Jan", "Kowalski", "78785285242", Address("99-111", "Krakow", "Stawowa 669"), Sex::Male, 5);
    }

    DataBase cut;
};

TEST_F(DataBaseRemovePersonFixture, shouldReturnInvalidIndexNumber) {
    auto result = cut.removeStudent(-3);
    EXPECT_EQ(result, ErrorCode::InvalidIndexNumber);
}

TEST_F(DataBaseRemovePersonFixture, shouldReturnIndexNumberNotFound) {
    auto result = cut.removeStudent(99);
    EXPECT_EQ(result, ErrorCode::IndexNumberNotFound);
}

TEST_F(DataBaseRemovePersonFixture, shouldRemoveStudent) {
    auto sizeBeforeRemoving = cut.data().size();
    auto result = cut.removeStudent(5);
    EXPECT_EQ(result, ErrorCode::Ok);
    EXPECT_EQ(cut.data().size(), sizeBeforeRemoving - 1);
}

TEST_F(DataBaseRemovePersonFixture, shouldReturnInvalidPesel) {
    auto result = cut.removePerson("55030101192");
    EXPECT_EQ(result, ErrorCode::InvalidPesel);
}

TEST_F(DataBaseRemovePersonFixture, shouldReturnPeselNotFound) {
    auto result = cut.removePerson("55030101193");
    EXPECT_EQ(result, ErrorCode::PeselNotFound);
}

TEST_F(DataBaseRemovePersonFixture, shouldRemovePerson) {
    auto sizeBeforeRemoving = cut.data().size();
    auto result = cut.removePerson("78785285242");
    EXPECT_EQ(result, ErrorCode::Ok);
    EXPECT_EQ(cut.data().size(), sizeBeforeRemoving - 1);
}

TEST_F(DataBaseRemovePersonFixture, shouldClearWholeDataBase) {
    cut.clearAll();
    EXPECT_EQ(cut.data().size(), 0);
}

class DataBaseSearchPersonFixture : public ::testing::Test {
public:
    DataBaseSearchPersonFixture() {
        cut.addStudent("Jan", "Kowalski", "78785285242", Address("99-111", "Krakow", "Stawowa 669"), Sex::Male, 5);
        cut.addEmployee("Monika", "Lubicz", "93847560327", Address("09-622", "Wolniki", "Skrzetuskiego 9"), Sex::Female, 4300);
        cut.addStudent("Janoslaw", "Kowalczyk", "78787878785", Address("99-112", "Krakow", "Stawowa 700"), Sex::Male, 6);
        cut.addEmployee("Krystian", "Zaremba", "34343434341", Address("44-200", "Rybnik", "Janasa 3"), Sex::Male, 3040);
    }

    DataBase cut;
};

TEST_F(DataBaseSearchPersonFixture, shouldFindOnePersonByLastName) {
    std::vector<std::shared_ptr<Person>> results;
    auto error = cut.searchStudentByLastName("Kowals", results);
    ASSERT_EQ(error, ErrorCode::Ok);
    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(cut.data().front(), results.front()); // sprawdzic czy porownanie shared ptrow dziala
}

TEST_F(DataBaseSearchPersonFixture, shouldFindTwoPeopleByLastName) {
    std::vector<std::shared_ptr<Person>> results;
    auto error = cut.searchStudentByLastName("Kowal", results);
    ASSERT_EQ(error, ErrorCode::Ok);
    EXPECT_EQ(results.size(), 2);
}

TEST_F(DataBaseSearchPersonFixture, shouldReturnLastNameNotFound) {
    std::vector<std::shared_ptr<Person>> results;
    auto error = cut.searchStudentByLastName("Abcdef", results);
    ASSERT_EQ(error, ErrorCode::LastNameNotFound);
    EXPECT_EQ(results.size(), 0);
}

TEST_F(DataBaseSearchPersonFixture, shouldFindOnePersonByPesel) {
    std::vector<std::shared_ptr<Person>> results;
    auto error = cut.searchStudentByPesel("78785285242", results);
    ASSERT_EQ(error, ErrorCode::Ok);
    EXPECT_EQ(results.size(), 1);
}

TEST_F(DataBaseSearchPersonFixture, shouldFindTwoPeopleByPesel) {
    std::vector<std::shared_ptr<Person>> results;
    auto error = cut.searchStudentByPesel("7878", results);
    ASSERT_EQ(error, ErrorCode::Ok);
    EXPECT_EQ(results.size(), 2);
}

TEST_F(DataBaseSearchPersonFixture, shouldReturnPeselNotFound) {
    std::vector<std::shared_ptr<Person>> results;
    auto error = cut.searchStudentByPesel("55030101193", results);
    ASSERT_EQ(error, ErrorCode::PeselNotFound);
    EXPECT_EQ(results.size(), 0);
}

class DataBaseSortingFixture : public ::testing::Test {
public:
    DataBaseSortingFixture() {
        cut.addEmployee("Monika", "Lubicz", "93847560327", Address("09-622", "Wolniki", "Skrzetuskiego 9"), Sex::Female, 4300);
        cut.addStudent("Jan", "Kowalski", "78785285242", Address("99-111", "Krakow", "Stawowa 669"), Sex::Male, 5);
        cut.addEmployee("Krystian", "Zaremba", "34343434341", Address("44-200", "Rybnik", "Janasa 3"), Sex::Male, 3040);
        cut.addStudent("Janoslaw", "Kowalczyk", "78787878785", Address("99-112", "Krakow", "Stawowa 700"), Sex::Male, 6);
        cut.addStudent("Lucja", "Kowalczyk", "55030101193", Address("99-112", "A", "B"), Sex::Female, 7);
    }

    DataBase cut;
};

TEST_F(DataBaseSortingFixture, shouldSortByLastName) {
    std::vector<std::shared_ptr<Person>> sorted;
    sorted.push_back(cut.data()[3]); // czy my tak mozemy??
    sorted.push_back(cut.data()[4]); // porownanie shared pointerow
    sorted.push_back(cut.data()[1]);
    sorted.push_back(cut.data()[0]);
    sorted.push_back(cut.data()[2]);

    cut.sortByLastName();

    for (size_t i = 0; i < sorted.size(); ++i) {
        EXPECT_EQ(cut.data()[i], sorted[i]);
    }

}