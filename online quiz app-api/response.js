function getBotResponse(input) {
  if (input == "sir shall i leave") {
    return "ok if you finish means kindly leave";
  } else if (input == "sir question is not visible") {
    return "check your network propertly";
  } else if (input == "i am unable to sumbit my quiz") {
    return "refresh the page once";
  }

  // Simple responses
  if (input == "hello") {
    return "Hello there!";
  } else if (input == "thank you sir") {
    return "thank you ";
  } else {
    return "Try asking something else!";
  }
}
