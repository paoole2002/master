struct AddOrderRequest;

bool CheckValidInput(const std::string& errorMessage);
void DiscardInputLine();
bool ParseAddOrderRequest(AddOrderRequest& request);
bool ParseCancelOrderRequest(long long& orderId);