#include "../include/pch.h"

void DiscardInputLine() {
    std::cin.clear(); // Reset error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool CheckValidInput(const std::string& errorMessage) {
    if (std::cin.eof()) {
        std::cout << "End of file reached. Exiting." << std::endl;
        exit(0);
    }
    else if (std::cin.fail()) {
        std::cerr << errorMessage.c_str();
        DiscardInputLine();
        return false;
    }

    return true;
}

bool ParseAddOrderRequest(AddOrderRequest& request) {
    std::string errorMessage;
    request.m_messageType = MessageType::AddOrderRequestType;

    // get orderId
    std::cin >> request.m_orderId;
    if (!CheckValidInput(errorMessage)) return false;
    std::cin.ignore(); // ignore comma

    // get side
    int side;
    std::cin >> side;
    errorMessage = "Failed to parse side. Discarding input.\n";
    if (!CheckValidInput(errorMessage)) return false;
    if (side != 0 && side != 1) {
        std::cerr << "Wrong side value (expected 0 ir 1). Discarding input.\n";
        DiscardInputLine();
        return false;
    }

    request.m_side = (Side)side;
    std::cin.ignore(); // ignore comma

    // get quantity
    std::cin >> request.m_quantity;
    errorMessage = "Failed to parse quantity. Discarding input.\n";
    if (!CheckValidInput(errorMessage)) return false;
    std::cin.ignore(); // ignore comma

    // get price
    std::cin >> request.m_price;
    errorMessage = "Failed to parse price. Discarding input.\n";
    if (!CheckValidInput(errorMessage)) return false;

    // If we made it here, an AddOrderRequest has been parsed.
    // Additionally, making an assumption that if the input entered up until
    // this point is valid, we consider the input valid. There might be comments
    // or other data succeeding the input in the same line, which, this
    // application elects to skip.
    DiscardInputLine();

    return true;
}

bool ParseCancelOrderRequest(long long& orderId) {
    std::cin >> orderId;
    std::string errorMessage = "Failed to parse orderId. Discarding input.\n";
    if (!CheckValidInput(errorMessage)) return false;

    return true;
}