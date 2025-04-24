constexpr uint8_t c_addOrRequestOrderSize = 5;
constexpr uint8_t c_cancelOrderRequestSize = 2;

enum MessageType {
    AddOrderRequestType = 0,
    CancelOrderRequest,
    TradeEvent,
    OrderFullyFilled,
    OrderPartiallyFilled
};

enum Side {
    Buy = 0,
    Sell = 1
};

struct AddOrderRequest {
    AddOrderRequest() = default;
    MessageType m_messageType;
    long long m_orderId;
    Side m_side;
    int m_quantity;
    double m_price;

    void PrintAddOrderRequest() {
        std::cout << "PringAddOrderRequest: ";
        std::cout << " orderId: " << m_orderId;
        std::cout << " side: " << m_side;
        std::cout << " quantity: " << m_quantity;
        std::cout << " price: " << m_price << "\n";
    }
};
