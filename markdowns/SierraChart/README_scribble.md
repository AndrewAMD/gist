# Sierra Chart Plugin for Zorro

This plugin works both as a broker plugin to Zorro Trading Automation and as a client to Sierra Chart in order to:
1) Get live market data, including market depth
2) Get historical market data
3) Trade algorithmically
4) Track your trading account

This plugin was written in Win32 C/C++ using Visual Studio 2017.

## Build Instructions

This plugin depends on the following libraries:

* Boost Asio 1.66 (for asynchronous network communications)
* Boost UUID (to generate order Client ID's)
* OpenSSL (for TLS 1.2 encryption)
* zlib (optional historical data compression)
* DTC Protocol library

Build in Visual Studio 2017 or greater, linking to the above dependencies.  This plugin must be compiled in 32-bit (x86) in order to be compatible with Zorro.

## Installation Instructions

To install the plugin, simply place the SierraChart.dll file in the Plugin folder where Zorro is installed.

## About Sierra Chart

Sierra Chart is a trading platform with support for many brokers.

Sierra Chart has a fully integrated DTC Server.  It has two dedicated ports:
1) One for all trading, current market data, account data, and position data.
2) One for all historical market data.

## Configuring Sierra Chart DTC Server

A Sierra Chart instance can be accessed locally or over the internet. This plugin only uses TLS encryption.  Unencrypted connections are not supported by this plugin.

To set up Sierra Chart's DTC Server:
* Open Sierra Chart
* Global Settings -> Data/Trade Service Settings
* SC Server Settings
  * Check "Enable DTC Protocol Server"
  * Check "Require TLS"
  * Optional: Check "Allow Trading"
  * Optional: Check "Require Authentication"
  * Optional: If you have multiple installations of Sierra Chart, make sure that each installation has unique DTC ports.  For example, installation 1 uses ports 11099, 11098, and 11097, and installation 2 uses ports 11096, 11095, and 11094 for the Listening Port, Historical Data Port, and the TLS Historical Data Port, respectively.

If you need multiple instances of Sierra Chart to trade with two brokers at the same time, you will need a second installation of Sierra Chart on your computer.  Do do this:
* Follow these instructions: https://www.sierrachart.com/index.php?page=doc/NewInstance.php
* Also, make sure that the DTC Ports are different for every

(TODO: Set up server instructions)
(TODO: Set up second server instructions)

## Configuring Zorro

(TODO: Define all parsed fields in Username)
(TODO: Define password


## Login Instructions

To login with the Ally Plugin, you will first need to set up API access with Ally Invest. After you have set up your account with Ally, you must do the following:

* Go to https://www.ally.com/invest/
* Click Log In and enter your credentials
* Click on your account (usually says "individual", depending on your type of account).
* At the top, go to "Tools" -> "Ally Invest API" -> "Manage Applications"
* Create a "Personal Application", and follow the steps. Your new application should have been created instantly.
* Scroll down. Under "Developer Applications", click on the application you created.
* You should see four scrambled keys.  You will need these.
* Open Zorro.  
* Set "Account" to "Real", and choose the "Ally Invest" plugin from the drop-down menus.
* Under "User", enter your account number (not to be confused with your website login username)
* For the password, paste the values in one after the other, in the exact order below (no spaces, no commas):
  1. Consumer Key
  2. Consumer Secret
  3. OAuth Token
  4. OAuth Token Secret

## Plugin Capabilities

The following standard Zorro Broker API functions have been implemented:

* BrokerOpen
* BrokerLogin
* BrokerTime
* BrokerAsset
* BrokerAccount
* BrokerHistory2
* BrokerBuy2 (orders only)
* BrokerTrade (orders only)
* BrokerCommand standard functions:
  * GET\_MAXTICKS
  * SET\_HWND
  * SET\_SYMBOL
  * GET\_VOLTYPE
  * SET\_VOLTYPE
  * GET\_PRICETYPE
  * SET\_PRICETYPE
  * SET\_ORDERTYPE
  * GET\_UUID
  * SET\_UUID
  * GET\_POSITION
  * GET\_COMPLIANCE
  * SET\_PATCH


In addition, BrokerCommand supports some newly-defined functions:
* SET\_DIVIDEND\_ADJ
* GET\_DTCSECURITYDEF
* EXAMPLE\_BC
  * Input: Only accepts 2, 3, or 4 as an input, for 2-leg, 3-leg, and 4-leg orders, respectively.
  * Returns 1 if command accepted, 0 if rejected.
  * To use, call the function and then call the orders immediately.
  * For example, if you SET_COMBO_LEGS to 2 and then request two options orders, the order will finally process after the second options order is received.
  * If the order fails, the last leg will return a failure.  The script writer will be responsible for zeroing out the prior legs.
  * All of the legs must have matching **expiration months** and **underlying symbols**.  Otherwise, the order will not be submitted.

## Known Issues
(TODO: list known issues)

## License

This project has an MIT-style license. See the LICENSE.md file for more details.

## Resources

* [The Zorro Project](http://zorro-project.com/)
* [The Zorro Project - Manual](http://zorro-project.com/manual/)
* [Ally Invest](https://www.ally.com/invest/)
* [Ally Invest API Documentation](https://www.ally.com/api/invest/documentation/getting-started/)

## Contact Info

For any questions and inquiries, I can be reached via email:

* Andrew M. Dolder
* andrew@vitaltrades.com
