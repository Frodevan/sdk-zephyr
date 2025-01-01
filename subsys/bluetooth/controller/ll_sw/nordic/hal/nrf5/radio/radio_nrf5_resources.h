/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Use the timer instance ID, not NRF_TIMERx directly, so that it can be checked
 * in radio_nrf5_ppi.h by the preprocessor.
 */
#if defined(CONFIG_BT_CTLR_TIFS_HW)
#define EVENT_TIMER_ID 0
#define EVENT_TIMER    _CONCAT(NRF_TIMER, EVENT_TIMER_ID)

/* Single timer feature not supported when using h/w tIFS switching */
#define HAL_RADIO_ISR_LATENCY_MAX_US 0U

/* Wrapper for EVENTS_END event generated by Radio peripheral at the very end of the transmission
 * or reception of a PDU on air. In case of regular PDU it is generated when last bit of CRC is
 * received or transmitted.
 */
#define HAL_RADIO_TRX_EVENTS_END HAL_RADIO_EVENTS_END

/* Wrapper for RADIO_SHORTS mask connecting EVENTS_END to EVENTS_DISABLE.
 * This is a default shortcut used to automatically disable Radio after end of PDU.
 */
#define NRF_RADIO_SHORTS_TRX_END_DISABLE_Msk HAL_RADIO_SHORTS_TRX_END_DISABLE_Msk

#define HAL_EVENT_TIMER_TRX_CC_OFFSET          0
#define HAL_EVENT_TIMER_TRX_EVENT              NRF_TIMER_EVENT_COMPARE0
#define HAL_EVENT_TIMER_READY_TASK             NRF_TIMER_TASK_CAPTURE0

#define HAL_EVENT_TIMER_HCTO_CC_OFFSET         1
#define HAL_EVENT_TIMER_HCTO_EVENT             NRF_TIMER_EVENT_COMPARE1
#define HAL_EVENT_TIMER_ADDRESS_TASK           NRF_TIMER_TASK_CAPTURE1

#define HAL_EVENT_TIMER_TRX_END_CC_OFFSET      2
#define HAL_EVENT_TIMER_TRX_END_TASK           NRF_TIMER_TASK_CAPTURE2

#define HAL_EVENT_TIMER_DEFERRED_TRX_CC_OFFSET 2
#define HAL_EVENT_TIMER_DEFERRED_TX_EVENT      NRF_TIMER_EVENT_COMPARE2

#define HAL_EVENT_TIMER_SAMPLE_CC_OFFSET       3
#define HAL_EVENT_TIMER_SAMPLE_TASK            NRF_TIMER_TASK_CAPTURE3

#define HAL_EVENT_TIMER_PA_LNA_CC_OFFSET       2
#define HAL_EVENT_TIMER_PA_LNA_PDN_CC_OFFSET   3

#else /* !CONFIG_BT_CTLR_TIFS_HW */
#if defined(CONFIG_BT_CTLR_SW_SWITCH_SINGLE_TIMER)
#define EVENT_TIMER_ID 4
#define EVENT_TIMER    _CONCAT(NRF_TIMER, EVENT_TIMER_ID)

#define SW_SWITCH_TIMER EVENT_TIMER

/* Radio ISR Latency to be considered with single timer used so that the PPI/
 * DPPI is disabled in time when the timer is cleared on radio end, so that
 * the timer compare should not trigger TXEN/RXEN immediately on radio end.
 * This value will be used as minimum turnaround time in setting up Rx to Tx
 * using radio_tmr_start_us under single timer use.
 * The value of 80 us is used considering 150 us TIFS minus the maximum rx
 * chain delay ~30 us, and minus the radio ramp up delay ~40 us.
 */
#define HAL_RADIO_ISR_LATENCY_MAX_US 80U

#if defined(CONFIG_BT_CTLR_PHY_CODED)
#define SW_SWITCH_TIMER_EVTS_COMP_BASE 4
#define SW_SWITCH_TIMER_EVTS_COMP_S2_BASE 6

/* Wrapper for EVENTS_END event generated by Radio peripheral at the very end of the transmission
 * or reception of a PDU on air. In case of regular PDU it is generated when last bit of CRC is
 * received or transmitted.
 */
#define HAL_RADIO_TRX_EVENTS_END HAL_RADIO_EVENTS_END

/* Wrapper for RADIO_SHORTS mask connecting EVENTS_END to EVENTS_DISABLE.
 * This is a default shortcut used to automatically disable Radio after end of PDU.
 */
#define NRF_RADIO_SHORTS_TRX_END_DISABLE_Msk HAL_RADIO_SHORTS_TRX_END_DISABLE_Msk

#define HAL_EVENT_TIMER_TRX_CC_OFFSET          0
#define HAL_EVENT_TIMER_TRX_EVENT              NRF_TIMER_EVENT_COMPARE0
#define HAL_EVENT_TIMER_READY_TASK             NRF_TIMER_TASK_CAPTURE0

#define HAL_EVENT_TIMER_HCTO_CC_OFFSET         1
#define HAL_EVENT_TIMER_HCTO_EVENT             NRF_TIMER_EVENT_COMPARE1
#define HAL_EVENT_TIMER_ADDRESS_TASK           NRF_TIMER_TASK_CAPTURE1

#define HAL_EVENT_TIMER_TRX_END_CC_OFFSET      2
#define HAL_EVENT_TIMER_TRX_END_TASK           NRF_TIMER_TASK_CAPTURE2

#define HAL_EVENT_TIMER_DEFERRED_TRX_CC_OFFSET 2
#define HAL_EVENT_TIMER_DEFERRED_TX_EVENT      NRF_TIMER_EVENT_COMPARE2

#define HAL_EVENT_TIMER_SAMPLE_CC_OFFSET       3
#define HAL_EVENT_TIMER_SAMPLE_TASK            NRF_TIMER_TASK_CAPTURE3

#define HAL_EVENT_TIMER_PA_LNA_CC_OFFSET       2
#define HAL_EVENT_TIMER_PA_LNA_PDN_CC_OFFSET   3

#else /* !CONFIG_BT_CTLR_PHY_CODED */
#define SW_SWITCH_TIMER_EVTS_COMP_BASE 4

/* Wrapper for EVENTS_END event generated by Radio peripheral at the very end of the transmission
 * or reception of a PDU on air. In case of regular PDU it is generated when last bit of CRC is
 * received or transmitted.
 */
#define HAL_RADIO_TRX_EVENTS_END HAL_RADIO_EVENTS_END

/* Wrapper for RADIO_SHORTS mask connecting EVENTS_END to EVENTS_DISABLE.
 * This is a default shortcut used to automatically disable Radio after end of PDU.
 */
#define NRF_RADIO_SHORTS_TRX_END_DISABLE_Msk HAL_RADIO_SHORTS_TRX_END_DISABLE_Msk

#define HAL_EVENT_TIMER_TRX_CC_OFFSET          0
#define HAL_EVENT_TIMER_TRX_EVENT              NRF_TIMER_EVENT_COMPARE0
#define HAL_EVENT_TIMER_READY_TASK             NRF_TIMER_TASK_CAPTURE0

#define HAL_EVENT_TIMER_HCTO_CC_OFFSET         1
#define HAL_EVENT_TIMER_HCTO_EVENT             NRF_TIMER_EVENT_COMPARE1
#define HAL_EVENT_TIMER_ADDRESS_TASK           NRF_TIMER_TASK_CAPTURE1

#define HAL_EVENT_TIMER_TRX_END_CC_OFFSET      2
#define HAL_EVENT_TIMER_TRX_END_TASK           NRF_TIMER_TASK_CAPTURE2

#define HAL_EVENT_TIMER_DEFERRED_TRX_CC_OFFSET 2
#define HAL_EVENT_TIMER_DEFERRED_TX_EVENT      NRF_TIMER_EVENT_COMPARE2

#define HAL_EVENT_TIMER_SAMPLE_CC_OFFSET       3
#define HAL_EVENT_TIMER_SAMPLE_TASK            NRF_TIMER_TASK_CAPTURE3

#define HAL_EVENT_TIMER_PA_LNA_CC_OFFSET       2
#define HAL_EVENT_TIMER_PA_LNA_PDN_CC_OFFSET   3
#endif /* !CONFIG_BT_CTLR_PHY_CODED */

#else /* !CONFIG_BT_CTLR_SW_SWITCH_SINGLE_TIMER */
#define EVENT_TIMER_ID 0
#define EVENT_TIMER    _CONCAT(NRF_TIMER, EVENT_TIMER_ID)

#define SW_SWITCH_TIMER NRF_TIMER1

/* When using dedicated timer used for tIFS switching, compensation to avoid
 * spurious TXEN/RXEN due to timer being clear is not needed.
 */
#define HAL_RADIO_ISR_LATENCY_MAX_US 0U

#define SW_SWITCH_TIMER_EVTS_COMP_BASE 0

#if defined(CONFIG_BT_CTLR_PHY_CODED)
#define SW_SWITCH_TIMER_EVTS_COMP_S2_BASE 2
#endif /* !CONFIG_BT_CTLR_PHY_CODED */

#if defined(CONFIG_BT_CTLR_DF)

#if defined(CONFIG_BT_CTLR_DF_PHYEND_OFFSET_COMPENSATION_ENABLE)
/* Allocate 2 adjacent channels for PHYEND delay compensation. Use the same channels as for
 * PHY CODED S2. The CTEINLINE may not be enabled for PHY CODED so PHYEND event is generated
 * at the same instant as END event. Hence the channels are used interchangeably.
 * That saves from use of another timer.
 */
#define SW_SWITCH_TIMER_EVTS_COMP_PHYEND_DELAY_COMPENSATION_BASE 2
#endif /* CONFIG_BT_CTLR_DF_PHYEND_OFFSET_COMPENSATION_ENABLE */

/* Wrapper for EVENTS_END event generated by Radio peripheral at the very end of the transmission
 * or reception of a PDU on air. In case of regular PDU it is generated when last bit of CRC is
 * received or transmitted.
 *
 * When direction finding is enabled a PDU may include Constant Tone Extension at its end. For PDU
 * including CTE EVENTS_PHYEND event is generated at very end of a PDU. In case there is no CTE in
 * a PDU the EVENTS_PHYEND event is generated in the same instant as EVENTS_END event.
 */
#define HAL_RADIO_TRX_EVENTS_END HAL_RADIO_EVENTS_PHYEND

/* Wrapper for RADIO_SHORTS mask connecting EVENTS_PHYEND to EVENTS_DISABLE.
 * This is a mask for SOC that has Direction Finding Extension in a Radio peripheral.
 * It enables shortcut for EVENTS_PHYEND event generated at very end to Radio EVENTS_DISABLE event.
 * In case there is a CTE in a PDU then EVENTS_PHYEND event is generated after the CTE.
 * If there is no CTE, it is generated in the same instant as EVENTS_END.
 */
#define NRF_RADIO_SHORTS_TRX_END_DISABLE_Msk HAL_RADIO_SHORTS_TRX_PHYEND_DISABLE_Msk

/* Delay of EVENTS_PHYEND event on receive PDU without CTE included when CTEINLINE is enabled */
#define RADIO_EVENTS_PHYEND_DELAY_US 16

/* Delay of CCM TASKS_CRYPT start in number of bits for Radio Bit counter */
#define CCM_TASKS_CRYPT_DELAY_BITS 3

#else /* !CONFIG_BT_CTLR_DF */
/* Wrapper for EVENTS_END event generated by Radio peripheral at the very end of the transmission
 * or reception of a PDU on air. In case of regular PDU it is generated when last bit of CRC is
 * received or transmitted.
 */
#define HAL_RADIO_TRX_EVENTS_END HAL_RADIO_EVENTS_END

/* Wrapper for RADIO_SHORTS mask connecting EVENTS_END to EVENTS_DISABLE.
 * This is a default shortcut used to automatically disable Radio after end of PDU.
 */
#define NRF_RADIO_SHORTS_TRX_END_DISABLE_Msk HAL_RADIO_SHORTS_TRX_END_DISABLE_Msk
#endif /* !CONFIG_BT_CTLR_DF */

#define HAL_EVENT_TIMER_TRX_CC_OFFSET          0
#define HAL_EVENT_TIMER_TRX_EVENT              NRF_TIMER_EVENT_COMPARE0
#define HAL_EVENT_TIMER_READY_TASK             NRF_TIMER_TASK_CAPTURE0

#define HAL_EVENT_TIMER_HCTO_CC_OFFSET         1
#define HAL_EVENT_TIMER_HCTO_EVENT             NRF_TIMER_EVENT_COMPARE1
#define HAL_EVENT_TIMER_ADDRESS_TASK           NRF_TIMER_TASK_CAPTURE1

#define HAL_EVENT_TIMER_TRX_END_CC_OFFSET      2
#define HAL_EVENT_TIMER_TRX_END_TASK           NRF_TIMER_TASK_CAPTURE2

#define HAL_EVENT_TIMER_DEFERRED_TRX_CC_OFFSET 2
#define HAL_EVENT_TIMER_DEFERRED_TX_EVENT      NRF_TIMER_EVENT_COMPARE2

#define HAL_EVENT_TIMER_SAMPLE_CC_OFFSET       3
#define HAL_EVENT_TIMER_SAMPLE_TASK            NRF_TIMER_TASK_CAPTURE3

#define HAL_EVENT_TIMER_PA_LNA_CC_OFFSET       2
#define HAL_EVENT_TIMER_PA_LNA_PDN_CC_OFFSET   3
#endif /* !CONFIG_BT_CTLR_SW_SWITCH_SINGLE_TIMER */
#endif /* !CONFIG_BT_CTLR_TIFS_HW */
