"""
Program: CS 115 Project 1 Phase 3
Author: Mackenzie Larson 
Description: This program tracks and calculates the averages, min and max price per share bought and sold, and the balance and difference from the beginning of the day 

"""

def main ():
    # Get the starting cash amount
    balance = float(input("Starting cash amount? "))

    #Original balance to store for difference at end of the day. 
    original_balance = balance 

    # Get the number of trades for the day
    num_trades = int(input("Number of trades for today? "))
    
    total_trades_bought = 0
    total_trades_sold = 0
    cumulative_num_shares = 0
    total_shares_bought = 0
    total_shares_sold = 0
    average_cost_of_shares_bought = 0.0
    average_cost_of_shares_sold = 0.0
    minimum_price_sold = None
    maximum_price_sold = None

    # Start Loop
    for i in range (1, num_trades+1):

        # For the firt iteration of the loop only. Must be a buy. 
        if i == 1:
            # Notify user they do not own shares yet, but display balance. 
            print("You do not own any shares, but have $", balance, " in cash.", sep="")

            print()

            # Get the number of shares to buy and the price per share. 
            num_shares = int(input("Number of shares to buy? "))
            price_per_share = float(input("Price per share? "))
            
            #New calculations to track cumulative shares, the cost of transaction, balance, total shares bought, the average of shares bought, min and max price of shares bought
            cumulative_num_shares = cumulative_num_shares + num_shares
            transaction_amount = num_shares * price_per_share
            balance = balance - transaction_amount
            total_shares_bought = total_shares_bought + num_shares
            average_cost_of_shares_bought = average_cost_of_shares_bought + price_per_share
            minimum_price_bought = price_per_share
            maximum_price_bought = price_per_share
            total_trades_bought = total_trades_bought + 1

            # Update user of balance and what their action did 
            print(num_shares, " shares for $", price_per_share, " per share cost $", transaction_amount, ".", sep="")
            print("Currently holding ", cumulative_num_shares, " shares and have $", balance, " in cash.", sep="")

            print()

        # For iterations of the loop greater than one and less than the last iteration of the loop. Can be a buy or a sell.
        elif 1 < i < num_trades:

            # Get the trade type
            action = input("Trade number " + str(i) + " (buy/sell)? ")

            # Path to go if the user's action is a buy
            if action == "buy":

                # Get the number of shares to buy
                num_shares = int(input("Number of shares to buy? "))
                # Get the price per share 
                price_per_share = float(input("Price per share? "))

                # Calculate the cost of the transaction
                transaction_amount = num_shares * price_per_share

                # If the transaction amount is less than the balance...
                if transaction_amount <= balance:

                    print(num_shares, " shares for $", price_per_share, " per share cost $", transaction_amount, ".", sep="")

                    # Update calculations 
                    cumulative_num_shares = cumulative_num_shares + num_shares
                    balance = balance - transaction_amount
                    total_shares_bought = total_shares_bought + num_shares
                    average_cost_of_shares_bought = average_cost_of_shares_bought + price_per_share
                    total_trades_bought = total_trades_bought + 1
                    
                    if price_per_share < minimum_price_bought:
                        minimum_price_bought = price_per_share

                    if price_per_share > maximum_price_bought:
                        maximum_price_bought = price_per_share 


                    print("Currently holding ", cumulative_num_shares, " shares and have $", balance, " in cash.", sep="")
                    
                    print()

                # If the transaction amount is more than the balance...
                else:
                    print("You do not have sufficient funds to purchase ", num_shares, " for $", price_per_share, " per share.", sep="")
                    print("Your current balance is $", balance, " but ", num_shares, " x $" , price_per_share, " = $", transaction_amount, ".", sep="")
                    print("Currently holding ", cumulative_num_shares, " shares and have $", balance, " in cash.", sep="")

                    print()

            # If the user picks sell as their action 
            else:
                #Get the number of shares to sell
                num_shares = int(input("Number of shares to sell? "))

                # If the number of shares to be sold is less than or equal to the number of shares the user has
                if num_shares <= cumulative_num_shares:
                    sale_price = float(input("Sale price? "))

                    # New calculations 
                    per_share_worth = num_shares * sale_price
                    cumulative_num_shares = cumulative_num_shares - num_shares
                    balance = balance + per_share_worth
                    total_shares_sold = total_shares_sold + num_shares
                    average_cost_of_shares_sold = average_cost_of_shares_sold + sale_price
                    total_trades_sold = total_trades_sold + 1

                    print(num_shares, " shares for $", sale_price, " per share worth $", per_share_worth, ".", sep="")
                    print("Currently holding ", cumulative_num_shares, " shares and have $", balance, " in cash.", sep="")


                    if minimum_price_sold is None or sale_price < minimum_price_sold:
                        minimum_price_sold = sale_price

                    if maximum_price_sold is None or sale_price > maximum_price_sold:
                        maximum_price_sold = sale_price
                        
                    
                    print()

                # If the number of shares to be sold is greater than what the user has...
                else:
                    print("You can't sell ", num_shares, " shares as you only have ", cumulative_num_shares, ".", sep="")
                    print("Currently holding ", cumulative_num_shares, " shares and have $", balance, " in cash.", sep="")

                    print()

        # For the last iteration of the loop. 
        else:
            # Get the trade type
            action = input("Trade number " + str(i) + " (buy/sell)? ")

            # If final action is a buy. 
            if action == "buy":

                # Get the number of shares to buy
                num_shares = int(input("Number of shares to buy? "))
                # Get the price per share 
                price_per_share = float(input("Price per share? "))

                # Calculate the cost of the transaction
                transaction_amount = num_shares * price_per_share

                #If the trade can continue: 
                if transaction_amount <= balance:

                    print(num_shares, " shares for $", price_per_share, " per share cost $", transaction_amount, ".", sep="")

                    # Update calculations
                    cumulative_num_shares = cumulative_num_shares + num_shares
                    balance = balance - transaction_amount
                    total_shares_bought = total_shares_bought + num_shares
                    average_cost_of_shares_bought = average_cost_of_shares_bought + price_per_share
                    total_trades_bought = total_trades_bought + 1

                    if price_per_share < minimum_price_bought:
                        minimum_price_bought = price_per_share

                    if price_per_share > maximum_price_bought:
                        maximum_price_bought = price_per_share 
                    
                    print()

                #If the trade cannot continue: 
                else:
                    
                    print("You do not have sufficient funds to purchase ", num_shares, " for $", price_per_share, " per share.", sep="")
                    print("Your current balance is $", balance, " but ", num_shares, " x $" , price_per_share, " = $", transaction_amount, ".", sep="")
                    print("Currently holding ", cumulative_num_shares, " shares and have $", balance, " in cash.", sep="")

                    print()

            # If final action is a sell
            else:
                #Get the number of shares to sell
                num_shares = int(input("Number of shares to sell? "))

                # If the trade can continue 
                if num_shares <= cumulative_num_shares:
                    sale_price = float(input("Sale price? "))

                    per_share_worth = num_shares * sale_price
                    cumulative_num_shares = cumulative_num_shares - num_shares
                    balance = balance + per_share_worth
                    total_shares_sold = total_shares_sold + num_shares
                    average_cost_of_shares_sold = average_cost_of_shares_sold + sale_price

                    if minimum_price_sold is None or sale_price < minimum_price_sold:
                        minimum_price_sold = sale_price

                    if maximum_price_sold is None or sale_price > maximum_price_sold:
                        maximum_price_sold = sale_price

                    print(num_shares, " shares for $", sale_price, " per share worth $", per_share_worth, ".", sep="")

                    total_trades_sold = total_trades_sold + 1
                    
                    print()

                # If the trade cannot continue.. 
                else:
                    print("You can't sell ", num_shares, " shares as you only have ", cumulative_num_shares, ".", sep="")
                    print("Currently holding ", cumulative_num_shares, " shares and have $", balance, " in cash.", sep="")
                    
                    print()

    #When the loop is over update user with total shares they have left and balance
    print("Trading day is almost over and you are left with ", cumulative_num_shares, " shares and $", balance, " in cash.", sep="")
    # Propmpt user to input final price to sell final shares
    price_to_sell_final_shares = float(input("Enter a price to sell these shares: "))

    # New transaction calculation 
    transaction_amount = cumulative_num_shares * price_to_sell_final_shares

    #Notify user of their final decision 
    print(cumulative_num_shares, " shares for $", price_to_sell_final_shares, " per share worth $", transaction_amount, ".", sep="")

    # Final calculations for closing statements 
    balance = balance + transaction_amount 
    total_shares_sold = total_shares_sold + cumulative_num_shares
    average_cost_of_shares_bought = average_cost_of_shares_bought / total_trades_bought
    average_cost_of_shares_sold = average_cost_of_shares_sold / total_trades_sold
    difference = original_balance - balance

    print()

    #Present user the totals of the day (averages, final balance, difference, ect.)
    print("Total shares bought for the day is ", total_shares_bought, " with an average of $", average_cost_of_shares_bought, " per share.", sep="")
    print("Minimum and maximum price per share bought are $", minimum_price_bought, " and $", maximum_price_bought, ", respectively.", sep="")
    print("Total shares sold for the day is ", total_shares_sold, " with an average of $", average_cost_of_shares_sold, " per share.", sep="")
    print("Minimim and maximum sale price per share are $", minimum_price_sold, " and $", maximum_price_sold, ", respectively.", sep="")
    print("End of day balance is ", balance, ", a loss of $", difference, ".", sep="")                

main()
