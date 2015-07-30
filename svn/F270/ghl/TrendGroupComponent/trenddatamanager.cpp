#include "trenddatamanager.h"
TrendDataManager::TrendDataManager(QObject *parent) :
    QObject(parent)
{
    initialize();
    sigAndSlotConnect();
}

TrendDataManager::~TrendDataManager()
{
    release();
}

void TrendDataManager::initialize()
{
}

void TrendDataManager::release()
{
}

void TrendDataManager::sigAndSlotConnect()
{

}
