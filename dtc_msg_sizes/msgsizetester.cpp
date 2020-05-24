// msgsizetester.cpp
// checks for struct sizes, for memory management purposes.

#include <iostream>
#include <algorithm>

#include <float.h>
#include <limits.h>
#include <string.h>
#include <memory.h> 
#include <stddef.h>
#include "DTCProtocol.h"

int main()
{
	using std::max;
	using namespace DTC;
	size_t mx_all = 0;
	
	printf("%6s: %4s %s\n", "Type", "Size", "Struct");
#define    maxx(structtype) {structtype msg1; mx_all = max(sizeof(structtype), mx_all); \
           printf("%6d: %4d %s\n",msg1.Type,msg1.Size, #structtype);}
	maxx(s_LogonRequest);
	maxx(s_LogonResponse);
	maxx(s_Logoff);
	maxx(s_Heartbeat);
	maxx(s_MarketDataFeedStatus);
	maxx(s_MarketDataFeedSymbolStatus);
	maxx(s_TradingSymbolStatus);
	maxx(s_MarketDataRequest);
	maxx(s_MarketDepthRequest);
	maxx(s_MarketDataReject);
	maxx(s_MarketDataSnapshot);
	maxx(s_MarketDataSnapshot_Int);
	//maxx(s_DepthEntry);
	maxx(s_MarketDepthSnapshotLevel);
	maxx(s_MarketDepthSnapshotLevelFloat);
	maxx(s_MarketDepthSnapshotLevel_Int);
	maxx(s_MarketDepthUpdateLevel);
	maxx(s_MarketDepthUpdateLevel_Int);
	maxx(s_MarketDepthUpdateLevelFloatWithMilliseconds);
	maxx(s_MarketDepthUpdateLevelNoTimestamp);
	maxx(s_MarketDataUpdateTradeNoTimestamp);
	maxx(s_MarketDataUpdateSessionSettlement);
	maxx(s_MarketDataUpdateSessionSettlement_Int);
	maxx(s_MarketDataUpdateSessionOpen);
	maxx(s_MarketDataUpdateSessionOpen_Int);
	maxx(s_MarketDataUpdateSessionNumTrades);
	maxx(s_MarketDataUpdateTradingSessionDate);
	maxx(s_MarketDepthReject);
	maxx(s_MarketDataUpdateTrade);
	maxx(s_MarketDataUpdateTrade_Int);
	maxx(s_MarketDataUpdateTradeWithUnbundledIndicator);
	maxx(s_MarketDataUpdateBidAsk);
	maxx(s_MarketDataUpdateBidAsk_Int);
	maxx(s_MarketDataUpdateBidAskCompact);
	maxx(s_MarketDataUpdateBidAskFloatWithMilliseconds);
	maxx(s_MarketDataUpdateBidAskNoTimeStamp);
	maxx(s_MarketDataUpdateTradeCompact);
	maxx(s_MarketDataUpdateSessionVolume);
	maxx(s_MarketDataUpdateOpenInterest);
	maxx(s_MarketDataUpdateSessionHigh);
	maxx(s_MarketDataUpdateSessionHigh_Int);
	maxx(s_MarketDataUpdateSessionLow);
	maxx(s_MarketDataUpdateSessionLow_Int);
	maxx(s_MarketDataUpdateLastTradeSnapshot);
	maxx(s_SubmitNewSingleOrder);
	maxx(s_SubmitNewSingleOrderInt);
	maxx(s_SubmitFlattenPositionOrder);
	maxx(s_CancelReplaceOrder);
	maxx(s_CancelReplaceOrderInt);
	maxx(s_CancelOrder);
	maxx(s_SubmitNewOCOOrder);
	maxx(s_SubmitNewOCOOrderInt);
	maxx(s_OpenOrdersRequest);
	maxx(s_HistoricalOrderFillsRequest);
	maxx(s_HistoricalOrderFillsReject);
	maxx(s_CurrentPositionsRequest);
	maxx(s_CurrentPositionsReject);
	maxx(s_OrderUpdate);
	maxx(s_OpenOrdersReject);
	maxx(s_HistoricalOrderFillResponse);
	maxx(s_PositionUpdate);
	maxx(s_TradeAccountsRequest);
	maxx(s_TradeAccountResponse);
	maxx(s_ExchangeListRequest);
	maxx(s_ExchangeListResponse);
	maxx(s_SymbolsForExchangeRequest);
	maxx(s_UnderlyingSymbolsForExchangeRequest);
	maxx(s_SymbolsForUnderlyingRequest);
	maxx(s_SymbolSearchRequest);
	maxx(s_SecurityDefinitionForSymbolRequest);
	maxx(s_SecurityDefinitionResponse);
	maxx(s_SecurityDefinitionReject);
	maxx(s_AccountBalanceRequest);
	maxx(s_AccountBalanceReject);
	maxx(s_AccountBalanceUpdate);
	maxx(s_AccountBalanceAdjustment);
	maxx(s_AccountBalanceAdjustmentReject);
	maxx(s_AccountBalanceAdjustmentComplete);
	maxx(s_HistoricalAccountBalancesRequest);
	maxx(s_HistoricalAccountBalancesReject);
	maxx(s_HistoricalAccountBalanceResponse);
	maxx(s_UserMessage);
	maxx(s_GeneralLogMessage);
	maxx(s_AlertMessage);
	maxx(s_JournalEntryAdd);
	maxx(s_JournalEntriesRequest);
	maxx(s_JournalEntriesReject);
	maxx(s_JournalEntryResponse);
	maxx(s_HistoricalPriceDataRequest);
	maxx(s_HistoricalPriceDataResponseHeader);
	maxx(s_HistoricalPriceDataReject);
	maxx(s_HistoricalPriceDataRecordResponse);
	maxx(s_HistoricalPriceDataTickRecordResponse);
	maxx(s_HistoricalPriceDataRecordResponse_Int);
	maxx(s_HistoricalPriceDataTickRecordResponse_Int);
	maxx(s_HistoricalPriceDataResponseTrailer);
#undef maxx
	size_t mx_hist = 0;
#define maxx(structtype) mx_hist = max(sizeof(structtype), mx_hist)
	maxx(s_LogonRequest);
	maxx(s_LogonResponse);
	maxx(s_Logoff);
	maxx(s_Heartbeat);
	maxx(s_HistoricalPriceDataRequest);
	maxx(s_HistoricalPriceDataResponseHeader);
	maxx(s_HistoricalPriceDataReject);
	maxx(s_HistoricalPriceDataRecordResponse);
	maxx(s_HistoricalPriceDataTickRecordResponse);
	maxx(s_HistoricalPriceDataRecordResponse_Int);
	maxx(s_HistoricalPriceDataTickRecordResponse_Int);
	maxx(s_HistoricalPriceDataResponseTrailer);
#undef maxx
	printf("-----------------------\n");
	printf("max message size = %d\n", mx_all);
	printf("max historical message size = %d\n", mx_hist);
	
}

/*  Output, as of May 24, 2020:

  Type: Size Struct
     1:  280 s_LogonRequest
     2:  256 s_LogonResponse
     5:  102 s_Logoff
     3:   16 s_Heartbeat
   100:    8 s_MarketDataFeedStatus
   116:   12 s_MarketDataFeedSymbolStatus
   138:   12 s_TradingSymbolStatus
   101:   96 s_MarketDataRequest
   102:   96 s_MarketDepthRequest
   103:  104 s_MarketDataReject
   104:  144 s_MarketDataSnapshot
   125:   96 s_MarketDataSnapshot_Int
   122:   56 s_MarketDepthSnapshotLevel
   145:   24 s_MarketDepthSnapshotLevelFloat
   132:   40 s_MarketDepthSnapshotLevel_Int
   106:   56 s_MarketDepthUpdateLevel
   133:   40 s_MarketDepthUpdateLevel_Int
   140:   29 s_MarketDepthUpdateLevelFloatWithMilliseconds
   141:   21 s_MarketDepthUpdateLevelNoTimestamp
   142:   18 s_MarketDataUpdateTradeNoTimestamp
   119:   24 s_MarketDataUpdateSessionSettlement
   131:   16 s_MarketDataUpdateSessionSettlement_Int
   120:   24 s_MarketDataUpdateSessionOpen
   128:   16 s_MarketDataUpdateSessionOpen_Int
   135:   16 s_MarketDataUpdateSessionNumTrades
   136:   12 s_MarketDataUpdateTradingSessionDate
   121:  104 s_MarketDepthReject
   107:   40 s_MarketDataUpdateTrade
   126:   32 s_MarketDataUpdateTrade_Int
   137:   40 s_MarketDataUpdateTradeWithUnbundledIndicator
   108:   40 s_MarketDataUpdateBidAsk
   127:   28 s_MarketDataUpdateBidAsk_Int
   117:   28 s_MarketDataUpdateBidAskCompact
   144:   32 s_MarketDataUpdateBidAskFloatWithMilliseconds
   143:   24 s_MarketDataUpdateBidAskNoTimeStamp
   112:   24 s_MarketDataUpdateTradeCompact
   113:   24 s_MarketDataUpdateSessionVolume
   124:   16 s_MarketDataUpdateOpenInterest
   114:   24 s_MarketDataUpdateSessionHigh
   129:   16 s_MarketDataUpdateSessionHigh_Int
   115:   24 s_MarketDataUpdateSessionLow
   130:   16 s_MarketDataUpdateSessionLow_Int
   134:   32 s_MarketDataUpdateLastTradeSnapshot
   208:  264 s_SubmitNewSingleOrder
   206:  264 s_SubmitNewSingleOrderInt
   209:  198 s_SubmitFlattenPositionOrder
   204:  160 s_CancelReplaceOrder
   205:  136 s_CancelReplaceOrderInt
   203:  100 s_CancelOrder
   201:  376 s_SubmitNewOCOOrder
   207:  360 s_SubmitNewOCOOrderInt
   300:   76 s_OpenOrdersRequest
   303:   88 s_HistoricalOrderFillsRequest
   308:  104 s_HistoricalOrderFillsReject
   305:   40 s_CurrentPositionsRequest
   307:  104 s_CurrentPositionsReject
   301:  688 s_OrderUpdate
   302:  104 s_OpenOrdersReject
   304:  384 s_HistoricalOrderFillResponse
   306:  200 s_PositionUpdate
   400:    8 s_TradeAccountsRequest
   401:   48 s_TradeAccountResponse
   500:    8 s_ExchangeListRequest
   501:   76 s_ExchangeListResponse
   502:   96 s_SymbolsForExchangeRequest
   503:   28 s_UnderlyingSymbolsForExchangeRequest
   504:   60 s_SymbolsForUnderlyingRequest
   508:   96 s_SymbolSearchRequest
   506:   88 s_SecurityDefinitionForSymbolRequest
   507:  356 s_SecurityDefinitionResponse
   509:  104 s_SecurityDefinitionReject
   601:   40 s_AccountBalanceRequest
   602:  104 s_AccountBalanceReject
   600:  216 s_AccountBalanceUpdate
   607:  160 s_AccountBalanceAdjustment
   608:  104 s_AccountBalanceAdjustmentReject
   609:   16 s_AccountBalanceAdjustmentComplete
   603:   48 s_HistoricalAccountBalancesRequest
   604:  104 s_HistoricalAccountBalancesReject
   606:  232 s_HistoricalAccountBalanceResponse
   700:  262 s_UserMessage
   701:  132 s_GeneralLogMessage
   702:  164 s_AlertMessage
   703:  272 s_JournalEntryAdd
   704:   16 s_JournalEntriesRequest
   705:  104 s_JournalEntriesReject
   706:  280 s_JournalEntryResponse
   800:  120 s_HistoricalPriceDataRequest
   801:   20 s_HistoricalPriceDataResponseHeader
   802:  108 s_HistoricalPriceDataReject
   803:   88 s_HistoricalPriceDataRecordResponse
   804:   48 s_HistoricalPriceDataTickRecordResponse
   805:   56 s_HistoricalPriceDataRecordResponse_Int
   806:   32 s_HistoricalPriceDataTickRecordResponse_Int
   807:   16 s_HistoricalPriceDataResponseTrailer
-----------------------
max message size = 688
max historical message size = 280

*/


