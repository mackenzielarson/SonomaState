"""
Program: CS 115 Project 1 Phase 1
Author: Mackenzie Larson 
Description: This program will compute the total cost or worth of each trade 
            (depending if it is a buy or a sell), and calculates the total 
            number of shares bought and sold.
"""

def main ():   
    # Get the number of trades
    num_trades = int(input("Number of trades for today? "))
    cumulative_num_shares_sold = 0  
    cumulative_num_shares_bought = 0 
                
    for i in range (1, num_trades+1):
        # Get the type of trade
        action= input("Trade number " + str(i) + " (buy/sell)? ")
    
        # Get the number of shares to trade
        if action == "buy":
            num_shares = int(input("Number of shares to buy? "))
        else: 
            num_shares = int(input("Number of shares to sell? "))
    
        # Get the price per share
        price_per_share = float(input("Price per share? "))
    
        # Add the number of shares bought or sold to the cumulative number of shares bought or sold
        if action == "buy": 
            cumulative_num_shares_bought = num_shares + cumulative_num_shares_bought
        else:
            cumulative_num_shares_sold = num_shares + cumulative_num_shares_sold

        print()
    
        # Tell user how many shares traded, how much per trade, and the total cost or worth of the trade
        if action == "buy":
            print(num_shares , " shares for $", price_per_share, " per share cost $",num_shares * price_per_share,"." , sep = "")
        else:
            print(num_shares , " shares for $", price_per_share, " per share worth $",num_shares * price_per_share,"." , sep = "")

        print()
        
    # Tell user how many total shares they bought and sold
    print("Bought" , cumulative_num_shares_bought, "shares and sold" , cumulative_num_shares_sold , "shares.")

main () 
