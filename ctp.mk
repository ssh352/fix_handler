$(BIN_PATH)/custom_md_spi.o: $(SRC_PATH)/ctp/market/custom_md_spi.cc
	$(COMPILE_COMMAND) -c -o $@ $<	
	
$(BIN_PATH)/custom_manager.o: $(SRC_PATH)/ctp/market/custom_manager.cc
	$(COMPILE_COMMAND) -c -o $@ $<
	
$(BIN_PATH)/MDWrapper.o: $(SRC_PATH)/ctp/market/MDWrapper.cc
	$(COMPILE_COMMAND) -c -o $@ $<
		
$(BIN_PATH)/ctp_market_application.o: $(SRC_PATH)/ctp/market/ctp_market_application.cc
	$(COMPILE_COMMAND) -c -o $@ $<	
	
$(BIN_PATH)/ctp_market_main_test.o: $(SRC_PATH)/main/ctp_maket/ctp_market_main.cc
	$(COMPILE_COMMAND) -c -o $@ $<	
	
$(BIN_PATH)/ApiCommand.o: $(SRC_PATH)/ctp/exchange/ApiCommand.cc
	$(COMPILE_COMMAND) -c -o $@ $<	
	
$(BIN_PATH)/ComfirmSettlementCommand.o: $(SRC_PATH)/ctp/exchange/ComfirmSettlementCommand.cc
	$(COMPILE_COMMAND) -c -o $@ $<		
	
$(BIN_PATH)/CommandQueue.o: $(SRC_PATH)/ctp/exchange/CommandQueue.cc
	$(COMPILE_COMMAND) -c -o $@ $<		
	
$(BIN_PATH)/MDAccountID.o: $(SRC_PATH)/ctp/market/MDAccountID.cc
	$(COMPILE_COMMAND) -c -o $@ $<		
	
$(BIN_PATH)/AccountID.o: $(SRC_PATH)/ctp/exchange/AccountID.cc
	$(COMPILE_COMMAND) -c -o $@ $<		
				
$(BIN_PATH)/InsertOrderCommand.o: $(SRC_PATH)/ctp/exchange/InsertOrderCommand.cc
	$(COMPILE_COMMAND) -c -o $@ $<		
	
$(BIN_PATH)/LoginCommand.o: $(SRC_PATH)/ctp/exchange/LoginCommand.cc
	$(COMPILE_COMMAND) -c -o $@ $<		
	
$(BIN_PATH)/LoginOutCommand.o: $(SRC_PATH)/ctp/exchange/LoginOutCommand.cc
	$(COMPILE_COMMAND) -c -o $@ $<		
	
$(BIN_PATH)/ReqQryTradeCommand.o: $(SRC_PATH)/ctp/exchange/ReqQryTradeCommand.cc
	$(COMPILE_COMMAND) -c -o $@ $<			
	
$(BIN_PATH)/ReqQryInstrumentCommand.o: $(SRC_PATH)/ctp/exchange/ReqQryInstrumentCommand.cc
	$(COMPILE_COMMAND) -c -o $@ $<			

$(BIN_PATH)/QueryOrderCommand.o: $(SRC_PATH)/ctp/exchange/QueryOrderCommand.cc
	$(COMPILE_COMMAND) -c -o $@ $<	
	
$(BIN_PATH)/QueryPositionCommand.o: $(SRC_PATH)/ctp/exchange/QueryPositionCommand.cc
	$(COMPILE_COMMAND) -c -o $@ $<		
	
$(BIN_PATH)/WithdrawOrderCommand.o: $(SRC_PATH)/ctp/exchange/WithdrawOrderCommand.cc
	$(COMPILE_COMMAND) -c -o $@ $<		
		
$(BIN_PATH)/communicator.o: $(SRC_PATH)/ctp/exchange/communicator.cc
	$(COMPILE_COMMAND) -c -o $@ $<
	
$(BIN_PATH)/ctp_trader_spi.o: $(SRC_PATH)/ctp/exchange/ctp_trader_spi.cc
	$(COMPILE_COMMAND) -c -o $@ $<	
	
$(BIN_PATH)/ctp_exchange_application.o: $(SRC_PATH)/ctp/exchange/ctp_exchange_application.cc
	$(COMPILE_COMMAND) -c -o $@ $<					

$(BIN_PATH)/ctp_exchange_main_test.o: $(SRC_PATH)/main/ctp_exchange/ctp_exchange_main.cc
	$(COMPILE_COMMAND) -c -o $@ $<	
	
$(BIN_PATH)/book_convert.o: $(SRC_PATH)/ctp/market/book_convert.cc
	$(COMPILE_COMMAND) -c -o $@ $<	
	
$(BIN_PATH)/mut_custom_manager.o: $(TEST_PATH)/ctp/market/mut_custom_manager.cc
	$(COMPILE_COMMAND) -c -o $@ $<	
	
$(BIN_PATH)/mut_custom_md_spi.o: $(TEST_PATH)/ctp/market/mut_custom_md_spi.cc
	$(COMPILE_COMMAND) -c -o $@ $<			
	
$(BIN_PATH)/mut_ctp_exchange.o: $(TEST_PATH)/ctp/exchange/mut_ctp_exchange.cc
	$(COMPILE_COMMAND) -c -o $@ $<	