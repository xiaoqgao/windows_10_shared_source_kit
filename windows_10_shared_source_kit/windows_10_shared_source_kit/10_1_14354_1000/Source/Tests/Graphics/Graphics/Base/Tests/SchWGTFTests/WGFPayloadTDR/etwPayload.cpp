/******************************Module*Header*******************************
* Module Name: WGFPayloadTDR.h
*
* D3D11 Graphics and Compute TDR workload test
*
* Author: David Flenniken [davidfl]
*
* Copyright (c) Microsoft Corporation.  All rights reserved.
**************************************************************************/
#include "internal.h"

#include <lddmcoreeventdefs.h>
#include <dxetwevt.hxx>
#include <DXGKernelConsumer.h>
#include <DxgKernelEventHelper.h>
#include <etwStatistics.h>
#include <DXGKernelStatistics.h>

#include "etwPayload.h"

CPayloadConsumer::CPayloadConsumer(CController* _petwController) :
    m_petwController(_petwController),
    m_bDisableGPUTimeout(false),
    m_bAccessBlocked(false),
    m_DelayContextScheduling(0),
    m_GlobalDelayContextScheduling(0),
    m_bRunning(false)
{
};
CPayloadConsumer::~CPayloadConsumer()
{
};

void CPayloadConsumer::Start()
{
    m_bRunning=true;
}
void CPayloadConsumer::Stop()
{
    m_bRunning=false;
}
bool CPayloadConsumer::Reset()
{
    bool bRet=true;
    if( m_bRunning )
    {
        // Reset should not be called when the class is actively collecting data!
        PATH_TRAP();
        bRet = false;
    }
    else
    {
        // zero out what we need too
        m_bDisableGPUTimeout = false;
        m_bAccessBlocked = false;
        m_DelayContextScheduling = 0;
        m_GlobalDelayContextScheduling = 0;
    }
    return bRet;
}

// We handle the Device creation event and look for the flags used to create the device.

void CPayloadConsumer::Device_Handler(PEVENT_RECORD pEvent)
{
    if( !m_bRunning )
    {
        // Don't count until the test says to Start() counting.
        return;
    }

    CDxgKernelEventHelper EH(pEvent);

    // Profile events are either Start or Stop events.
    if(EH.IsStart() || EH.IsDCStart())
    {
        DWORD dwProcessId=NULL;

        // This new flag is only supported with the new crimson events. Also, we only
        // want to process the event from our process - the one that we created.
        if( !EH.IsClassic() )
        {
            dwProcessId = (DWORD)EH.GetProperty<ULONG>(L"hProcessId");

            if( dwProcessId == GetCurrentProcessId() )
            {
                // This is an event generated by our process.
                bool bDisableGPUTime = EH.GetProperty<bool>(L"DisableGpuTimeout");
                if( bDisableGPUTime )
                {
                    m_bDisableGPUTimeout = bDisableGPUTime;
                }
            }
        }

    }
}

void CPayloadConsumer::BlockGpuAccess_Handler(PEVENT_RECORD pEvent)
{
    if( !m_bRunning )
    {
        // Don't count until the test says to Start() counting.
        return;
    }

    CDxgKernelEventHelper EH(pEvent);
    // These events are always Info events.

    DWORD dwProcessId=NULL;
    dwProcessId = (DWORD)EH.GetProperty<ULONG>(L"hProcessId");

    if( dwProcessId == GetCurrentProcessId() )
    {
        // This is an event says that we were locked out.
        m_bAccessBlocked = true;
    }    
}

void CPayloadConsumer::DelayContextScheduling_Handler(PEVENT_RECORD pEvent)
{
    if( !m_bRunning )
    {
        // Don't count until the test says to Start() counting.
        return;
    }

    CDxgKernelEventHelper EH(pEvent);
    // These events are always Info events.

    DWORD dwProcessId=NULL;
    dwProcessId = (DWORD)EH.GetProperty<ULONG>(L"hProcessId");

    m_GlobalDelayContextScheduling++;
    if( dwProcessId == GetCurrentProcessId() )
    {
        // This is an event says that we were locked out.
        m_DelayContextScheduling++;
    }    
}
