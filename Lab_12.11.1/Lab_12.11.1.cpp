#include <iostream>
#include <fstream>
#include <string>

// Structure representing a respondent's questionnaire
struct Respondent
{
    int age;
    std::string gender;
    std::string education;
    std::string answer;
};

// Binary tree node
struct TreeNode {
    Respondent data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Respondent& respondent) : data(respondent), left(nullptr), right(nullptr) {}
};

// Function to create a new binary tree node
TreeNode* createNode(const Respondent& respondent) 
{
    return new TreeNode(respondent);
}

// Function to insert a new node into the binary tree
void insertNode(TreeNode*& node, const Respondent& respondent)
 {
    if (node == nullptr) {
        node = createNode(respondent);
        return;
    }

    if (respondent.age < node->data.age)
        insertNode(node->left, respondent);
    else
        insertNode(node->right, respondent);
}

// Function to print all questionnaires and answers
void printTree(TreeNode* node) 
{
    if (node == nullptr)
        return;

    std::cout << "Age: " << node->data.age << std::endl;
    std::cout << "Gender: " << node->data.gender << std::endl;
    std::cout << "Education: " << node->data.education << std::endl;
    std::cout << "Answer: " << node->data.answer << std::endl;
    std::cout << std::endl;

    printTree(node->left);
    printTree(node->right);
}

// Recursively write data to a file
void saveDataToFileRecursive(TreeNode* node, std::ofstream& file) {
    if (node == nullptr)
        return;

    file << "Age: " << node->data.age << std::endl;
    file << "Gender: " << node->data.gender << std::endl;
    file << "Education: " << node->data.education << std::endl;
    file << "Answer: " << node->data.answer << std::endl;
    file << std::endl;

    saveDataToFileRecursive(node->left, file);
    saveDataToFileRecursive(node->right, file);
}

// Function to save questionnaires to a file
void saveDataToFile(TreeNode* node, const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Could not open file for writing." << std::endl;
        return;
    }

    file << "Questionnaires of respondents:" << std::endl;
    file << "-------------------" << std::endl;

    saveDataToFileRecursive(node, file);

    file.close();

    std::cout << "The data has been saved to a file " << filename << "." << std::endl;
}

// Function to load questionnaires from a file
TreeNode* loadDataFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Could not open file for reading." << std::endl;
        return nullptr;
    }

    TreeNode* root = nullptr;
    std::string line;

    while (std::getline(file, line)) {
        Respondent respondent;

        if (line.empty())
            continue;

        std::size_t pos = line.find(":");
        if (pos == std::string::npos) {
            std::cerr << "Invalid data format in the file." << std::endl;
            file.close();
            return nullptr;
        }

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);  // Read the line after the colon and space
        //std::size_t genderSize = line.find("woman");
        //std::string genderLine = line.substr(genderSize);

        if (key == "Age") 
        {
            respondent.age = std::stoi(value);
        }
        else if (key == "Gender")
        {
            //respondent.gender = genderSize;
            respondent.education = value;
        }
        else if (key == "Education")
        {
            //respondent.education = valueString;
           respondent.education = value;
        }
        else if (key == "Answer")
 {
            respondent.answer = value;
            insertNode(root, respondent);
        }
    }

    file.close();

    std::cout << "Data has been loaded from a file " << filename << "." << std::endl;

    return root;
}




// Function to count the answers to a questionnaire
void countAnswers(TreeNode* node, int& count, const std::string& gender, int ageLimit, const std::string& education, const std::string& answer)
{
    if (node == nullptr)
        return;

    if (node->data.gender == gender && node->data.age > ageLimit && node->data.education == education && node->data.answer == answer)
        count++;

    countAnswers(node->left, count, gender, ageLimit, education, answer);
    countAnswers(node->right, count, gender, ageLimit, education, answer);
}

int main() {
    TreeNode* root = nullptr;

    int choice;
    do {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Input questionnaire" << std::endl;
        std::cout << "2. Display all questionnaires and answers" << std::endl;
        std::cout << "3. Save data to file" << std::endl;
        std::cout << "4. Load data from file" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Choose an action: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            Respondent respondent;
            std::cout << "Enter age: ";
            std::cin >> respondent.age;

            std::cin.ignore(); // Ignore the newline character left in the input buffer

            std::cout << "Enter gender: ";
            std::getline(std::cin, respondent.gender);

            std::cout << "Enter education: ";
            std::getline(std::cin, respondent.education);

            std::cout << "Enter your answer (Yes/No): ";
            std::cin >> respondent.answer;
            insertNode(root, respondent);
            break;
        }

        case 2: {
            std::cout << "Questionnaires of respondents:" << std::endl;
            std::cout << "-------------------" << std::endl;
            printTree(root);
            break;
        }
        case 3: {
            std::string filename;
            std::cout << "Enter a file name to save: ";
            std::cin >> filename;
            saveDataToFile(root, filename);
            break;
        }
        case 4: {
            std::string filename;
            std::cout << "Enter the name of the file to load: ";
            std::cin >> filename;
            root = loadDataFromFile(filename);
            break;
        }
        case 5: {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        default: {
            std::cout << "Wrong choice. Try again." << std::endl;
            break;
        }
        }
    } while (choice != 5);

    // Analyzing questionnaire responses
    int count1 = 0;
    countAnswers(root, count1, "man", 40, "high", "Yes");
    std::cout << "1) Men over 40 years of age with a higher education who answered \"Yes\": " << count1 << std::endl;

    int count2 = 0;
    countAnswers(root, count2, "woman", 30, "average", "No");
    std::cout << "2) Women under 30 years of age with a secondary education who answered \"No\": " << count2 << std::endl;

    int count3 = 0;
    countAnswers(root, count3, "man", 25, "primary", "Yes");
    std::cout << "3) Men under 25 years of age with a primary education who answered \"Yes\": " << count3 << std::endl;

    return 0;
}
