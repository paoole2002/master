#include "../include/pch.h"

int main() {
    MatchingEngine matchingEngine;
    int messageType;
    std::string errorMessage = "Failed to parse message type. Discarding input.\n";;
    while (true) {
        std::cin >> messageType;
        if (!CheckValidInput(errorMessage)) {
            continue;
        }

        std::cin.ignore(); // ignore comma

        switch (messageType) {
            case MessageType::AddOrderRequestType:
                AddOrderRequest request;
                if (ParseAddOrderRequest(request)) {
                    matchingEngine.ExecuteAddOrderRequest();
                    request.PrintAddOrderRequest();
                }
                break;
            case MessageType::CancelOrderRequest:
                long long orderId;
                if (ParseCancelOrderRequest(orderId)) {
                    matchingEngine.ExecuteCancelOrderRequest();
                }
                break;
            default:
                std::cerr << "Wrong msgtype. Expected values are 0 and 1.\n";
                break;
        }
        
        if (std::cin.eof()) {
            std::cout << "End of file reached. Exiting." << std::endl;
            return 0;
        }
    }

    return 0;
}