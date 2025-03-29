# Simple Accountancy
This is a simple console based application aimed at aiding a normal person get a better understanding of their spending habits. It does this by allowing the user to download their bank statement in .csv format and import it into the program where it will provide a breakdown of their monthly spending habits and if they are overspending or not.

## Features
- Supported Currencies:
    - GBP, £
    - EUR, €
    - USD, $
- Supported Banks by Country:
    - UK
        - Nationwide
- Supported OSs:
    - Windows 11
- Analysis Functions:
    - Average monthly spends across period organised by category
    - Average monthly income vs expenses over period

## Usage
No installer provided yet, code is developed within MSVS using C++20 in Windows 11. Behaviour/success on other platforms is currently untested (would love to know though!).

Requires the following additional Microsoft libraries to be installed and linked:
- propsys.lib
- shlwapi.lib
- comctl32.lib

## Future Plans
If you have any suggestions or find any bugs (especially to do with other compilers/OSs, etc.) please use the 'Feature Request' or 'Bug Report' templates when creating a [new issue](https://github.com/StableDynamics/Simple-Accountancy/issues).

## Acknowledgements
This repo reproduces aspects of the Microsoft Windows Common Item Dialog Samples - https://github.com/microsoft/Windows-classic-samples
This repo uses code from nlohmann-json - https://github.com/nlohmann/json