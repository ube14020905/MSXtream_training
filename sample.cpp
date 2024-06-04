void NSEStreamingData::frameQuoteMPB(struct interactiveMbpData *tInterMbpData)
{
    Segment *segment = NULL;

    if (!ExchSegments::isExchSupported(feedType.c_str(), segment))
    {
        return;
    }

    char cSymbol[32];
    sprintf(cSymbol, "%d_%s", tInterMbpData->iToken, feedType.c_str());
    QuoteMap::iterator iQuoteCache = quoteCache.find(cSymbol);

    if (iQuoteCache == quoteCache.end())
    {
        struct quote_packet_t pkt = {};
        quoteCache[cSymbol] = pkt;
        iQuoteCache = quoteCache.find(cSymbol);
    }

    double divisor = segment->priceDivisor;

    sprintf(iQuoteCache->second.cSymbol, "%s", cSymbol);
    sprintf(iQuoteCache->second.cExchange, "%s", segment->excName.c_str());

    iQuoteCache->second.dLastPrice = tInterMbpData->iLastTradedPrice / divisor;
    iQuoteCache->second.dOpenPrice = tInterMbpData->iOpenPrice / divisor;
    iQuoteCache->second.dHighPrice = tInterMbpData->iHighPrice / divisor;
    iQuoteCache->second.dLowPrice = tInterMbpData->iLowPrice / divisor;
    iQuoteCache->second.dClosePrice = tInterMbpData->iClosePrice / divisor;

    bool isNormalMktPreOpen = (strcasecmp(marketCache[iQuoteCache->second.cExchange].c_str(), MarketStatus::NORMAL_MKT_PRE_OPEN) == 0);

    if (iQuoteCache->second.dOpenPrice > 0 && !isNormalMktPreOpen && tInterMbpData->iLastTradedPrice > 0)
    {
        iQuoteCache->second.dLastPrice = tInterMbpData->iLastTradedPrice / divisor;
        iQuoteCache->second.dIntradayChange = iQuoteCache->second.dLastPrice - iQuoteCache->second.dOpenPrice;
        iQuoteCache->second.dIntradayChangePercent = truncf((iQuoteCache->second.dIntradayChange / iQuoteCache->second.dOpenPrice) * 100 * 100.0) / 100.0;
    }

    if (iQuoteCache->second.dIntradayChange == 0.0)
    {
        iQuoteCache->second.dIntradayChangePercent = 0;
    }

    iQuoteCache->second.dAvgPrice = tInterMbpData->iAverageTradePrice / divisor;
    iQuoteCache->second.lTotalVolume = tInterMbpData->iVolumeTradedToday;
    iQuoteCache->second.lLastTradedVolume = tInterMbpData->iLastTradeQty;
    iQuoteCache->second.dTotalTradeValue = ((iQuoteCache->second.dAvgPrice * iQuoteCache->second.lTotalVolume) / 10000000);
    iQuoteCache->second.lTotalBuyQty = tInterMbpData->dTotalBuyQty;
    iQuoteCache->second.lTotalSellQty = tInterMbpData->dTotalSellQty;

    if (segment->marketOpen)
    {
        if (iQuoteCache->second.dClosePrice > 0)
        {
            iQuoteCache->second.dPClosePrice = iQuoteCache->second.dClosePrice;
        }
    }

    if (iQuoteCache->second.dPClosePrice > 0 && tInterMbpData->iLastTradedPrice > 0 && !isNormalMktPreOpen)
    {
        iQuoteCache->second.dLastPrice = tInterMbpData->iLastTradedPrice / divisor;
        double dClose = iQuoteCache->second.dPClosePrice;
        double dChange = iQuoteCache->second.dLastPrice - dClose;
        double dChangePercent = 0.00;

        if (dClose > 0)
        {
            dChangePercent = truncf(dChange * 100 * 100.0 / dClose) / 100.0;
        }

        iQuoteCache->second.dChange = dChange;
        iQuoteCache->second.dChangePercent = dChangePercent;
    }

    if (iQuoteCache->second.dHighPrice > 0 && iQuoteCache->second.dYearHigh < iQuoteCache->second.dHighPrice)
    {
        iQuoteCache->second.dYearHigh = iQuoteCache->second.dHighPrice;
    }

    if (iQuoteCache->second.dLowPrice > 0 && iQuoteCache->second.dYearLow > iQuoteCache->second.dLowPrice)
    {
        iQuoteCache->second.dYearLow = iQuoteCache->second.dLowPrice;
    }

    if (iQuoteCache->second.dHighPrice > 0 && iQuoteCache->second.dHighPrice > iQuoteCache->second.dAllTimeHigh)
    {
        iQuoteCache->second.dAllTimeHigh = iQuoteCache->second.dHighPrice;
    }

    if (iQuoteCache->second.dLowPrice > 0 && iQuoteCache->second.dLowPrice < iQuoteCache->second.dAllTimeLow)
    {
        iQuoteCache->second.dAllTimeLow = iQuoteCache->second.dLowPrice;
    }

    iQuoteCache->second.lLastTradedTime = tInterMbpData->iLastTradedTime;

    for (uint8_t i = 0; i < 10; i++)
    {
        if (i < 5)
        {
            iQuoteCache->second.bid_entry[i % 5].dPrice = tInterMbpData->mbpInfo[i].iPrice / divisor;
            iQuoteCache->second.bid_entry[i % 5].lQty = tInterMbpData->mbpInfo[i].iQty;
            iQuoteCache->second.bid_entry[i % 5].lOrders = tInterMbpData->mbpInfo[i].sNoOfOrders;
        }
        else
        {
            iQuoteCache->second.ask_entry[i % 5].dPrice = tInterMbpData->mbpInfo[i].iPrice / divisor;
            iQuoteCache->second.ask_entry[i % 5].lQty = tInterMbpData->mbpInfo[i].iQty;
            iQuoteCache->second.ask_entry[i % 5].lOrders = tInterMbpData->mbpInfo[i].sNoOfOrders;
        }
    }

    sendToProxy(tInterMbpData, &iQuoteCache->second);
    lSequenceNumber += 1;
}
