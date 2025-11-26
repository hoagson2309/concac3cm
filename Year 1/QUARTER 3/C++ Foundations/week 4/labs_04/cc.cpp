// handle short options (e.g., -r5, -cblue)
else if (arg[0] == '-' && arg[1] != '-' && arg.length() > 2){
    char option = arg[1];
    std::string value = arg.substr(2);

    switch (option){
        case 'r':
            try{
                result.repeat = std::stoi(value);  //conver string into an integer
                if(result.repeat < -1){
                    throw std::invalid_argument("Repeat value must be -1 or greater.");
                }
            }
            catch (const std::invalid_argument&){
                throw std::invalid_argument("Invalid repeat value: " + value);
            }
            break;
        case 'c':
            try{
                result.color = from_string(value);
            }
            catch (const std::invalid_argument&){
                throw std::invalid_argument("Invalid color value: " + value);
            }
            break;
        default:
            throw std::invalid_argument("Unknown short option: -" + std::string(1, option));
        }
}