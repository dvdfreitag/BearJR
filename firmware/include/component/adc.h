/**
 * \file
 *
 * \brief Component description for ADC
 *
 * Copyright (c) 2016 Atmel Corporation,
 *                    a wholly owned subsidiary of Microchip Technology Inc.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

#ifndef _SAMD20_ADC_COMPONENT_
#define _SAMD20_ADC_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR ADC */
/* ========================================================================== */
/** \addtogroup SAMD20_ADC Analog Digital Converter */
/*@{*/

#define ADC_U2204
#define REV_ADC                     0x111

#define ADC_CTRLA_OFFSET            0x00         /**< \brief (ADC_CTRLA offset) Control A */
#define ADC_CTRLA_RESETVALUE        _U(0x00);    /**< \brief (ADC_CTRLA reset_value) Control A */

#define ADC_CTRLA_SWRST_Pos         0            /**< \brief (ADC_CTRLA) Software Reset */
#define ADC_CTRLA_SWRST             (_U(0x1) << ADC_CTRLA_SWRST_Pos)
#define ADC_CTRLA_ENABLE_Pos        1            /**< \brief (ADC_CTRLA) Enable */
#define ADC_CTRLA_ENABLE            (_U(0x1) << ADC_CTRLA_ENABLE_Pos)
#define ADC_CTRLA_RUNSTDBY_Pos      2            /**< \brief (ADC_CTRLA) Run in Standby */
#define ADC_CTRLA_RUNSTDBY          (_U(0x1) << ADC_CTRLA_RUNSTDBY_Pos)
#define ADC_CTRLA_MASK              _U(0x07)     /**< \brief (ADC_CTRLA) MASK Register */

#define ADC_REFCTRL_OFFSET          0x01         /**< \brief (ADC_REFCTRL offset) Reference Control */
#define ADC_REFCTRL_RESETVALUE      _U(0x00);    /**< \brief (ADC_REFCTRL reset_value) Reference Control */

#define ADC_REFCTRL_REFSEL_Pos      0            /**< \brief (ADC_REFCTRL) Reference Selection */
#define ADC_REFCTRL_REFSEL_Msk      (_U(0xF) << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL(value)   (ADC_REFCTRL_REFSEL_Msk & ((value) << ADC_REFCTRL_REFSEL_Pos))
#define   ADC_REFCTRL_REFSEL_INT1V_Val    _U(0x0)   /**< \brief (ADC_REFCTRL) 1.0V voltage reference */
#define   ADC_REFCTRL_REFSEL_INTVCC0_Val  _U(0x1)   /**< \brief (ADC_REFCTRL) 1/1.48 VDDANA */
#define   ADC_REFCTRL_REFSEL_INTVCC1_Val  _U(0x2)   /**< \brief (ADC_REFCTRL) 1/2 VDDANA (only for VDDANA > 2.0V) */
#define   ADC_REFCTRL_REFSEL_AREFA_Val    _U(0x3)   /**< \brief (ADC_REFCTRL) External reference */
#define   ADC_REFCTRL_REFSEL_AREFB_Val    _U(0x4)   /**< \brief (ADC_REFCTRL) External reference */
#define ADC_REFCTRL_REFSEL_INT1V    (ADC_REFCTRL_REFSEL_INT1V_Val  << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL_INTVCC0  (ADC_REFCTRL_REFSEL_INTVCC0_Val << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL_INTVCC1  (ADC_REFCTRL_REFSEL_INTVCC1_Val << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL_AREFA    (ADC_REFCTRL_REFSEL_AREFA_Val  << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFSEL_AREFB    (ADC_REFCTRL_REFSEL_AREFB_Val  << ADC_REFCTRL_REFSEL_Pos)
#define ADC_REFCTRL_REFCOMP_Pos     7            /**< \brief (ADC_REFCTRL) Reference Buffer Offset Compensation Enable */
#define ADC_REFCTRL_REFCOMP         (_U(0x1) << ADC_REFCTRL_REFCOMP_Pos)
#define ADC_REFCTRL_MASK            _U(0x8F)     /**< \brief (ADC_REFCTRL) MASK Register */

#define ADC_AVGCTRL_OFFSET          0x02         /**< \brief (ADC_AVGCTRL offset) Average Control */
#define ADC_AVGCTRL_RESETVALUE      _U(0x00);    /**< \brief (ADC_AVGCTRL reset_value) Average Control */

#define ADC_AVGCTRL_SAMPLENUM_Pos   0            /**< \brief (ADC_AVGCTRL) Number of Samples to be Collected */
#define ADC_AVGCTRL_SAMPLENUM_Msk   (_U(0xF) << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM(value) (ADC_AVGCTRL_SAMPLENUM_Msk & ((value) << ADC_AVGCTRL_SAMPLENUM_Pos))
#define   ADC_AVGCTRL_SAMPLENUM_1_Val     _U(0x0)   /**< \brief (ADC_AVGCTRL) 1 sample */
#define   ADC_AVGCTRL_SAMPLENUM_2_Val     _U(0x1)   /**< \brief (ADC_AVGCTRL) 2 samples */
#define   ADC_AVGCTRL_SAMPLENUM_4_Val     _U(0x2)   /**< \brief (ADC_AVGCTRL) 4 samples */
#define   ADC_AVGCTRL_SAMPLENUM_8_Val     _U(0x3)   /**< \brief (ADC_AVGCTRL) 8 samples */
#define   ADC_AVGCTRL_SAMPLENUM_16_Val    _U(0x4)   /**< \brief (ADC_AVGCTRL) 16 samples */
#define   ADC_AVGCTRL_SAMPLENUM_32_Val    _U(0x5)   /**< \brief (ADC_AVGCTRL) 32 samples */
#define   ADC_AVGCTRL_SAMPLENUM_64_Val    _U(0x6)   /**< \brief (ADC_AVGCTRL) 64 samples */
#define   ADC_AVGCTRL_SAMPLENUM_128_Val   _U(0x7)   /**< \brief (ADC_AVGCTRL) 128 samples */
#define   ADC_AVGCTRL_SAMPLENUM_256_Val   _U(0x8)   /**< \brief (ADC_AVGCTRL) 256 samples */
#define   ADC_AVGCTRL_SAMPLENUM_512_Val   _U(0x9)   /**< \brief (ADC_AVGCTRL) 512 samples */
#define   ADC_AVGCTRL_SAMPLENUM_1024_Val  _U(0xA)   /**< \brief (ADC_AVGCTRL) 1024 samples */
#define ADC_AVGCTRL_SAMPLENUM_1     (ADC_AVGCTRL_SAMPLENUM_1_Val   << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_2     (ADC_AVGCTRL_SAMPLENUM_2_Val   << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_4     (ADC_AVGCTRL_SAMPLENUM_4_Val   << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_8     (ADC_AVGCTRL_SAMPLENUM_8_Val   << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_16    (ADC_AVGCTRL_SAMPLENUM_16_Val  << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_32    (ADC_AVGCTRL_SAMPLENUM_32_Val  << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_64    (ADC_AVGCTRL_SAMPLENUM_64_Val  << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_128   (ADC_AVGCTRL_SAMPLENUM_128_Val << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_256   (ADC_AVGCTRL_SAMPLENUM_256_Val << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_512   (ADC_AVGCTRL_SAMPLENUM_512_Val << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_SAMPLENUM_1024  (ADC_AVGCTRL_SAMPLENUM_1024_Val << ADC_AVGCTRL_SAMPLENUM_Pos)
#define ADC_AVGCTRL_ADJRES_Pos      4            /**< \brief (ADC_AVGCTRL) Adjusting Result / Division Coefficient */
#define ADC_AVGCTRL_ADJRES_Msk      (_U(0x7) << ADC_AVGCTRL_ADJRES_Pos)
#define ADC_AVGCTRL_ADJRES(value)   (ADC_AVGCTRL_ADJRES_Msk & ((value) << ADC_AVGCTRL_ADJRES_Pos))
#define ADC_AVGCTRL_MASK            _U(0x7F)     /**< \brief (ADC_AVGCTRL) MASK Register */

#define ADC_SAMPCTRL_OFFSET         0x03         /**< \brief (ADC_SAMPCTRL offset) Sampling Time Control */
#define ADC_SAMPCTRL_RESETVALUE     _U(0x00);    /**< \brief (ADC_SAMPCTRL reset_value) Sampling Time Control */

#define ADC_SAMPCTRL_SAMPLEN_Pos    0            /**< \brief (ADC_SAMPCTRL) Sampling Time Length */
#define ADC_SAMPCTRL_SAMPLEN_Msk    (_U(0x3F) << ADC_SAMPCTRL_SAMPLEN_Pos)
#define ADC_SAMPCTRL_SAMPLEN(value) (ADC_SAMPCTRL_SAMPLEN_Msk & ((value) << ADC_SAMPCTRL_SAMPLEN_Pos))
#define ADC_SAMPCTRL_MASK           _U(0x3F)     /**< \brief (ADC_SAMPCTRL) MASK Register */

#define ADC_CTRLB_OFFSET            0x04         /**< \brief (ADC_CTRLB offset) Control B */
#define ADC_CTRLB_RESETVALUE        _U(0x0000);  /**< \brief (ADC_CTRLB reset_value) Control B */

#define ADC_CTRLB_DIFFMODE_Pos      0            /**< \brief (ADC_CTRLB) Differential Mode */
#define ADC_CTRLB_DIFFMODE          (_U(0x1) << ADC_CTRLB_DIFFMODE_Pos)
#define ADC_CTRLB_LEFTADJ_Pos       1            /**< \brief (ADC_CTRLB) Left Adjusted Result */
#define ADC_CTRLB_LEFTADJ           (_U(0x1) << ADC_CTRLB_LEFTADJ_Pos)
#define ADC_CTRLB_FREERUN_Pos       2            /**< \brief (ADC_CTRLB) Free Running Mode */
#define ADC_CTRLB_FREERUN           (_U(0x1) << ADC_CTRLB_FREERUN_Pos)
#define ADC_CTRLB_CORREN_Pos        3            /**< \brief (ADC_CTRLB) Digital Correction Logic Enabled */
#define ADC_CTRLB_CORREN            (_U(0x1) << ADC_CTRLB_CORREN_Pos)
#define ADC_CTRLB_RESSEL_Pos        4            /**< \brief (ADC_CTRLB) Conversion Result Resolution */
#define ADC_CTRLB_RESSEL_Msk        (_U(0x3) << ADC_CTRLB_RESSEL_Pos)
#define ADC_CTRLB_RESSEL(value)     (ADC_CTRLB_RESSEL_Msk & ((value) << ADC_CTRLB_RESSEL_Pos))
#define   ADC_CTRLB_RESSEL_12BIT_Val      _U(0x0)   /**< \brief (ADC_CTRLB) 12-bit result */
#define   ADC_CTRLB_RESSEL_16BIT_Val      _U(0x1)   /**< \brief (ADC_CTRLB) For averaging mode output */
#define   ADC_CTRLB_RESSEL_10BIT_Val      _U(0x2)   /**< \brief (ADC_CTRLB) 10-bit result */
#define   ADC_CTRLB_RESSEL_8BIT_Val       _U(0x3)   /**< \brief (ADC_CTRLB) 8-bit result */
#define ADC_CTRLB_RESSEL_12BIT      (ADC_CTRLB_RESSEL_12BIT_Val    << ADC_CTRLB_RESSEL_Pos)
#define ADC_CTRLB_RESSEL_16BIT      (ADC_CTRLB_RESSEL_16BIT_Val    << ADC_CTRLB_RESSEL_Pos)
#define ADC_CTRLB_RESSEL_10BIT      (ADC_CTRLB_RESSEL_10BIT_Val    << ADC_CTRLB_RESSEL_Pos)
#define ADC_CTRLB_RESSEL_8BIT       (ADC_CTRLB_RESSEL_8BIT_Val     << ADC_CTRLB_RESSEL_Pos)
#define ADC_CTRLB_PRESCALER_Pos     8            /**< \brief (ADC_CTRLB) Prescaler Configuration */
#define ADC_CTRLB_PRESCALER_Msk     (_U(0x7) << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_PRESCALER(value)  (ADC_CTRLB_PRESCALER_Msk & ((value) << ADC_CTRLB_PRESCALER_Pos))
#define   ADC_CTRLB_PRESCALER_DIV4_Val    _U(0x0)   /**< \brief (ADC_CTRLB) Peripheral clock divided by 4 */
#define   ADC_CTRLB_PRESCALER_DIV8_Val    _U(0x1)   /**< \brief (ADC_CTRLB) Peripheral clock divided by 8 */
#define   ADC_CTRLB_PRESCALER_DIV16_Val   _U(0x2)   /**< \brief (ADC_CTRLB) Peripheral clock divided by 16 */
#define   ADC_CTRLB_PRESCALER_DIV32_Val   _U(0x3)   /**< \brief (ADC_CTRLB) Peripheral clock divided by 32 */
#define   ADC_CTRLB_PRESCALER_DIV64_Val   _U(0x4)   /**< \brief (ADC_CTRLB) Peripheral clock divided by 64 */
#define   ADC_CTRLB_PRESCALER_DIV128_Val  _U(0x5)   /**< \brief (ADC_CTRLB) Peripheral clock divided by 128 */
#define   ADC_CTRLB_PRESCALER_DIV256_Val  _U(0x6)   /**< \brief (ADC_CTRLB) Peripheral clock divided by 256 */
#define   ADC_CTRLB_PRESCALER_DIV512_Val  _U(0x7)   /**< \brief (ADC_CTRLB) Peripheral clock divided by 512 */
#define ADC_CTRLB_PRESCALER_DIV4    (ADC_CTRLB_PRESCALER_DIV4_Val  << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_PRESCALER_DIV8    (ADC_CTRLB_PRESCALER_DIV8_Val  << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_PRESCALER_DIV16   (ADC_CTRLB_PRESCALER_DIV16_Val << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_PRESCALER_DIV32   (ADC_CTRLB_PRESCALER_DIV32_Val << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_PRESCALER_DIV64   (ADC_CTRLB_PRESCALER_DIV64_Val << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_PRESCALER_DIV128  (ADC_CTRLB_PRESCALER_DIV128_Val << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_PRESCALER_DIV256  (ADC_CTRLB_PRESCALER_DIV256_Val << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_PRESCALER_DIV512  (ADC_CTRLB_PRESCALER_DIV512_Val << ADC_CTRLB_PRESCALER_Pos)
#define ADC_CTRLB_MASK              _U(0x073F)   /**< \brief (ADC_CTRLB) MASK Register */

#define ADC_WINCTRL_OFFSET          0x08         /**< \brief (ADC_WINCTRL offset) Window Monitor Control */
#define ADC_WINCTRL_RESETVALUE      _U(0x00);    /**< \brief (ADC_WINCTRL reset_value) Window Monitor Control */

#define ADC_WINCTRL_WINMODE_Pos     0            /**< \brief (ADC_WINCTRL) Window Monitor Mode */
#define ADC_WINCTRL_WINMODE_Msk     (_U(0x7) << ADC_WINCTRL_WINMODE_Pos)
#define ADC_WINCTRL_WINMODE(value)  (ADC_WINCTRL_WINMODE_Msk & ((value) << ADC_WINCTRL_WINMODE_Pos))
#define   ADC_WINCTRL_WINMODE_DISABLE_Val _U(0x0)   /**< \brief (ADC_WINCTRL) No window mode (default) */
#define   ADC_WINCTRL_WINMODE_MODE1_Val   _U(0x1)   /**< \brief (ADC_WINCTRL) Mode 1: RESULT > WINLT */
#define   ADC_WINCTRL_WINMODE_MODE2_Val   _U(0x2)   /**< \brief (ADC_WINCTRL) Mode 2: RESULT < WINUT */
#define   ADC_WINCTRL_WINMODE_MODE3_Val   _U(0x3)   /**< \brief (ADC_WINCTRL) Mode 3: WINLT < RESULT < WINUT */
#define   ADC_WINCTRL_WINMODE_MODE4_Val   _U(0x4)   /**< \brief (ADC_WINCTRL) Mode 4: !(WINLT < RESULT < WINUT) */
#define ADC_WINCTRL_WINMODE_DISABLE (ADC_WINCTRL_WINMODE_DISABLE_Val << ADC_WINCTRL_WINMODE_Pos)
#define ADC_WINCTRL_WINMODE_MODE1   (ADC_WINCTRL_WINMODE_MODE1_Val << ADC_WINCTRL_WINMODE_Pos)
#define ADC_WINCTRL_WINMODE_MODE2   (ADC_WINCTRL_WINMODE_MODE2_Val << ADC_WINCTRL_WINMODE_Pos)
#define ADC_WINCTRL_WINMODE_MODE3   (ADC_WINCTRL_WINMODE_MODE3_Val << ADC_WINCTRL_WINMODE_Pos)
#define ADC_WINCTRL_WINMODE_MODE4   (ADC_WINCTRL_WINMODE_MODE4_Val << ADC_WINCTRL_WINMODE_Pos)
#define ADC_WINCTRL_MASK            _U(0x07)     /**< \brief (ADC_WINCTRL) MASK Register */

#define ADC_SWTRIG_OFFSET           0x0C         /**< \brief (ADC_SWTRIG offset) Software Trigger */
#define ADC_SWTRIG_RESETVALUE       _U(0x00);    /**< \brief (ADC_SWTRIG reset_value) Software Trigger */

#define ADC_SWTRIG_FLUSH_Pos        0            /**< \brief (ADC_SWTRIG) ADC Conversion Flush */
#define ADC_SWTRIG_FLUSH            (_U(0x1) << ADC_SWTRIG_FLUSH_Pos)
#define ADC_SWTRIG_START_Pos        1            /**< \brief (ADC_SWTRIG) ADC Start Conversion */
#define ADC_SWTRIG_START            (_U(0x1) << ADC_SWTRIG_START_Pos)
#define ADC_SWTRIG_MASK             _U(0x03)     /**< \brief (ADC_SWTRIG) MASK Register */

#define ADC_INPUTCTRL_OFFSET        0x10         /**< \brief (ADC_INPUTCTRL offset) Inputs Control */
#define ADC_INPUTCTRL_RESETVALUE    _U(0x00000000); /**< \brief (ADC_INPUTCTRL reset_value) Inputs Control */

#define ADC_INPUTCTRL_MUXPOS_Pos    0            /**< \brief (ADC_INPUTCTRL) Positive MUX Input Selection */
#define ADC_INPUTCTRL_MUXPOS_Msk    (_U(0x1F) << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS(value) (ADC_INPUTCTRL_MUXPOS_Msk & ((value) << ADC_INPUTCTRL_MUXPOS_Pos))
#define   ADC_INPUTCTRL_MUXPOS_PIN0_Val   _U(0x0)   /**< \brief (ADC_INPUTCTRL) ADC AIN0 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN1_Val   _U(0x1)   /**< \brief (ADC_INPUTCTRL) ADC AIN1 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN2_Val   _U(0x2)   /**< \brief (ADC_INPUTCTRL) ADC AIN2 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN3_Val   _U(0x3)   /**< \brief (ADC_INPUTCTRL) ADC AIN3 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN4_Val   _U(0x4)   /**< \brief (ADC_INPUTCTRL) ADC AIN4 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN5_Val   _U(0x5)   /**< \brief (ADC_INPUTCTRL) ADC AIN5 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN6_Val   _U(0x6)   /**< \brief (ADC_INPUTCTRL) ADC AIN6 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN7_Val   _U(0x7)   /**< \brief (ADC_INPUTCTRL) ADC AIN7 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN8_Val   _U(0x8)   /**< \brief (ADC_INPUTCTRL) ADC AIN8 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN9_Val   _U(0x9)   /**< \brief (ADC_INPUTCTRL) ADC AIN9 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN10_Val  _U(0xA)   /**< \brief (ADC_INPUTCTRL) ADC AIN10 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN11_Val  _U(0xB)   /**< \brief (ADC_INPUTCTRL) ADC AIN11 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN12_Val  _U(0xC)   /**< \brief (ADC_INPUTCTRL) ADC AIN12 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN13_Val  _U(0xD)   /**< \brief (ADC_INPUTCTRL) ADC AIN13 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN14_Val  _U(0xE)   /**< \brief (ADC_INPUTCTRL) ADC AIN14 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN15_Val  _U(0xF)   /**< \brief (ADC_INPUTCTRL) ADC AIN15 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN16_Val  _U(0x10)   /**< \brief (ADC_INPUTCTRL) ADC AIN16 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN17_Val  _U(0x11)   /**< \brief (ADC_INPUTCTRL) ADC AIN17 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN18_Val  _U(0x12)   /**< \brief (ADC_INPUTCTRL) ADC AIN18 Pin */
#define   ADC_INPUTCTRL_MUXPOS_PIN19_Val  _U(0x13)   /**< \brief (ADC_INPUTCTRL) ADC AIN19 Pin */
#define   ADC_INPUTCTRL_MUXPOS_TEMP_Val   _U(0x18)   /**< \brief (ADC_INPUTCTRL) Temperature Reference */
#define   ADC_INPUTCTRL_MUXPOS_BANDGAP_Val _U(0x19)   /**< \brief (ADC_INPUTCTRL) Bandgap Voltage */
#define   ADC_INPUTCTRL_MUXPOS_SCALEDCOREVCC_Val _U(0x1A)   /**< \brief (ADC_INPUTCTRL) 1/4  Scaled Core Supply */
#define   ADC_INPUTCTRL_MUXPOS_SCALEDIOVCC_Val _U(0x1B)   /**< \brief (ADC_INPUTCTRL) 1/4  Scaled I/O Supply */
#define   ADC_INPUTCTRL_MUXPOS_DAC_Val    _U(0x1C)   /**< \brief (ADC_INPUTCTRL) DAC Output */
#define ADC_INPUTCTRL_MUXPOS_PIN0   (ADC_INPUTCTRL_MUXPOS_PIN0_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN1   (ADC_INPUTCTRL_MUXPOS_PIN1_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN2   (ADC_INPUTCTRL_MUXPOS_PIN2_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN3   (ADC_INPUTCTRL_MUXPOS_PIN3_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN4   (ADC_INPUTCTRL_MUXPOS_PIN4_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN5   (ADC_INPUTCTRL_MUXPOS_PIN5_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN6   (ADC_INPUTCTRL_MUXPOS_PIN6_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN7   (ADC_INPUTCTRL_MUXPOS_PIN7_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN8   (ADC_INPUTCTRL_MUXPOS_PIN8_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN9   (ADC_INPUTCTRL_MUXPOS_PIN9_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN10  (ADC_INPUTCTRL_MUXPOS_PIN10_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN11  (ADC_INPUTCTRL_MUXPOS_PIN11_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN12  (ADC_INPUTCTRL_MUXPOS_PIN12_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN13  (ADC_INPUTCTRL_MUXPOS_PIN13_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN14  (ADC_INPUTCTRL_MUXPOS_PIN14_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN15  (ADC_INPUTCTRL_MUXPOS_PIN15_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN16  (ADC_INPUTCTRL_MUXPOS_PIN16_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN17  (ADC_INPUTCTRL_MUXPOS_PIN17_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN18  (ADC_INPUTCTRL_MUXPOS_PIN18_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_PIN19  (ADC_INPUTCTRL_MUXPOS_PIN19_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_TEMP   (ADC_INPUTCTRL_MUXPOS_TEMP_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_BANDGAP (ADC_INPUTCTRL_MUXPOS_BANDGAP_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_SCALEDCOREVCC (ADC_INPUTCTRL_MUXPOS_SCALEDCOREVCC_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_SCALEDIOVCC (ADC_INPUTCTRL_MUXPOS_SCALEDIOVCC_Val << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXPOS_DAC    (ADC_INPUTCTRL_MUXPOS_DAC_Val  << ADC_INPUTCTRL_MUXPOS_Pos)
#define ADC_INPUTCTRL_MUXNEG_Pos    8            /**< \brief (ADC_INPUTCTRL) Negative MUX Input Selection */
#define ADC_INPUTCTRL_MUXNEG_Msk    (_U(0x1F) << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG(value) (ADC_INPUTCTRL_MUXNEG_Msk & ((value) << ADC_INPUTCTRL_MUXNEG_Pos))
#define   ADC_INPUTCTRL_MUXNEG_PIN0_Val   _U(0x0)   /**< \brief (ADC_INPUTCTRL) ADC AIN0 Pin */
#define   ADC_INPUTCTRL_MUXNEG_PIN1_Val   _U(0x1)   /**< \brief (ADC_INPUTCTRL) ADC AIN1 Pin */
#define   ADC_INPUTCTRL_MUXNEG_PIN2_Val   _U(0x2)   /**< \brief (ADC_INPUTCTRL) ADC AIN2 Pin */
#define   ADC_INPUTCTRL_MUXNEG_PIN3_Val   _U(0x3)   /**< \brief (ADC_INPUTCTRL) ADC AIN3 Pin */
#define   ADC_INPUTCTRL_MUXNEG_PIN4_Val   _U(0x4)   /**< \brief (ADC_INPUTCTRL) ADC AIN4 Pin */
#define   ADC_INPUTCTRL_MUXNEG_PIN5_Val   _U(0x5)   /**< \brief (ADC_INPUTCTRL) ADC AIN5 Pin */
#define   ADC_INPUTCTRL_MUXNEG_PIN6_Val   _U(0x6)   /**< \brief (ADC_INPUTCTRL) ADC AIN6 Pin */
#define   ADC_INPUTCTRL_MUXNEG_PIN7_Val   _U(0x7)   /**< \brief (ADC_INPUTCTRL) ADC AIN7 Pin */
#define   ADC_INPUTCTRL_MUXNEG_GND_Val    _U(0x18)   /**< \brief (ADC_INPUTCTRL) Internal ground */
#define   ADC_INPUTCTRL_MUXNEG_IOGND_Val  _U(0x19)   /**< \brief (ADC_INPUTCTRL) IO ground */
#define ADC_INPUTCTRL_MUXNEG_PIN0   (ADC_INPUTCTRL_MUXNEG_PIN0_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_PIN1   (ADC_INPUTCTRL_MUXNEG_PIN1_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_PIN2   (ADC_INPUTCTRL_MUXNEG_PIN2_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_PIN3   (ADC_INPUTCTRL_MUXNEG_PIN3_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_PIN4   (ADC_INPUTCTRL_MUXNEG_PIN4_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_PIN5   (ADC_INPUTCTRL_MUXNEG_PIN5_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_PIN6   (ADC_INPUTCTRL_MUXNEG_PIN6_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_PIN7   (ADC_INPUTCTRL_MUXNEG_PIN7_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_GND    (ADC_INPUTCTRL_MUXNEG_GND_Val  << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_MUXNEG_IOGND  (ADC_INPUTCTRL_MUXNEG_IOGND_Val << ADC_INPUTCTRL_MUXNEG_Pos)
#define ADC_INPUTCTRL_INPUTSCAN_Pos 16           /**< \brief (ADC_INPUTCTRL) Number of Input Channels Included in Scan */
#define ADC_INPUTCTRL_INPUTSCAN_Msk (_U(0xF) << ADC_INPUTCTRL_INPUTSCAN_Pos)
#define ADC_INPUTCTRL_INPUTSCAN(value) (ADC_INPUTCTRL_INPUTSCAN_Msk & ((value) << ADC_INPUTCTRL_INPUTSCAN_Pos))
#define ADC_INPUTCTRL_INPUTOFFSET_Pos 20           /**< \brief (ADC_INPUTCTRL) Positive MUX Setting Offset */
#define ADC_INPUTCTRL_INPUTOFFSET_Msk (_U(0xF) << ADC_INPUTCTRL_INPUTOFFSET_Pos)
#define ADC_INPUTCTRL_INPUTOFFSET(value) (ADC_INPUTCTRL_INPUTOFFSET_Msk & ((value) << ADC_INPUTCTRL_INPUTOFFSET_Pos))
#define ADC_INPUTCTRL_GAIN_Pos      24           /**< \brief (ADC_INPUTCTRL) Gain Factor Selection */
#define ADC_INPUTCTRL_GAIN_Msk      (_U(0xF) << ADC_INPUTCTRL_GAIN_Pos)
#define ADC_INPUTCTRL_GAIN(value)   (ADC_INPUTCTRL_GAIN_Msk & ((value) << ADC_INPUTCTRL_GAIN_Pos))
#define   ADC_INPUTCTRL_GAIN_1X_Val       _U(0x0)   /**< \brief (ADC_INPUTCTRL) 1x */
#define   ADC_INPUTCTRL_GAIN_2X_Val       _U(0x1)   /**< \brief (ADC_INPUTCTRL) 2x */
#define   ADC_INPUTCTRL_GAIN_4X_Val       _U(0x2)   /**< \brief (ADC_INPUTCTRL) 4x */
#define   ADC_INPUTCTRL_GAIN_8X_Val       _U(0x3)   /**< \brief (ADC_INPUTCTRL) 8x */
#define   ADC_INPUTCTRL_GAIN_16X_Val      _U(0x4)   /**< \brief (ADC_INPUTCTRL) 16x */
#define   ADC_INPUTCTRL_GAIN_DIV2_Val     _U(0xF)   /**< \brief (ADC_INPUTCTRL) 1/2x */
#define ADC_INPUTCTRL_GAIN_1X       (ADC_INPUTCTRL_GAIN_1X_Val     << ADC_INPUTCTRL_GAIN_Pos)
#define ADC_INPUTCTRL_GAIN_2X       (ADC_INPUTCTRL_GAIN_2X_Val     << ADC_INPUTCTRL_GAIN_Pos)
#define ADC_INPUTCTRL_GAIN_4X       (ADC_INPUTCTRL_GAIN_4X_Val     << ADC_INPUTCTRL_GAIN_Pos)
#define ADC_INPUTCTRL_GAIN_8X       (ADC_INPUTCTRL_GAIN_8X_Val     << ADC_INPUTCTRL_GAIN_Pos)
#define ADC_INPUTCTRL_GAIN_16X      (ADC_INPUTCTRL_GAIN_16X_Val    << ADC_INPUTCTRL_GAIN_Pos)
#define ADC_INPUTCTRL_GAIN_DIV2     (ADC_INPUTCTRL_GAIN_DIV2_Val   << ADC_INPUTCTRL_GAIN_Pos)
#define ADC_INPUTCTRL_MASK          _U(0x0FFF1F1F) /**< \brief (ADC_INPUTCTRL) MASK Register */

#define ADC_EVCTRL_OFFSET           0x14         /**< \brief (ADC_EVCTRL offset) Event Control */
#define ADC_EVCTRL_RESETVALUE       _U(0x00);    /**< \brief (ADC_EVCTRL reset_value) Event Control */

#define ADC_EVCTRL_STARTEI_Pos      0            /**< \brief (ADC_EVCTRL) Start Conversion Event In */
#define ADC_EVCTRL_STARTEI          (_U(0x1) << ADC_EVCTRL_STARTEI_Pos)
#define ADC_EVCTRL_SYNCEI_Pos       1            /**< \brief (ADC_EVCTRL) Synchronization Event In */
#define ADC_EVCTRL_SYNCEI           (_U(0x1) << ADC_EVCTRL_SYNCEI_Pos)
#define ADC_EVCTRL_RESRDYEO_Pos     4            /**< \brief (ADC_EVCTRL) Result Ready Event Out */
#define ADC_EVCTRL_RESRDYEO         (_U(0x1) << ADC_EVCTRL_RESRDYEO_Pos)
#define ADC_EVCTRL_WINMONEO_Pos     5            /**< \brief (ADC_EVCTRL) Window Monitor Event Out */
#define ADC_EVCTRL_WINMONEO         (_U(0x1) << ADC_EVCTRL_WINMONEO_Pos)
#define ADC_EVCTRL_MASK             _U(0x33)     /**< \brief (ADC_EVCTRL) MASK Register */

#define ADC_INTENCLR_OFFSET         0x16         /**< \brief (ADC_INTENCLR offset) Interrupt Enable Clear */
#define ADC_INTENCLR_RESETVALUE     _U(0x00);    /**< \brief (ADC_INTENCLR reset_value) Interrupt Enable Clear */

#define ADC_INTENCLR_RESRDY_Pos     0            /**< \brief (ADC_INTENCLR) Result Ready Interrupt Enable */
#define ADC_INTENCLR_RESRDY         (_U(0x1) << ADC_INTENCLR_RESRDY_Pos)
#define ADC_INTENCLR_OVERRUN_Pos    1            /**< \brief (ADC_INTENCLR) Overrun Interrupt Enable */
#define ADC_INTENCLR_OVERRUN        (_U(0x1) << ADC_INTENCLR_OVERRUN_Pos)
#define ADC_INTENCLR_WINMON_Pos     2            /**< \brief (ADC_INTENCLR) Window Monitor Interrupt Enable */
#define ADC_INTENCLR_WINMON         (_U(0x1) << ADC_INTENCLR_WINMON_Pos)
#define ADC_INTENCLR_SYNCRDY_Pos    3            /**< \brief (ADC_INTENCLR) Synchronization Ready Interrupt Enable */
#define ADC_INTENCLR_SYNCRDY        (_U(0x1) << ADC_INTENCLR_SYNCRDY_Pos)
#define ADC_INTENCLR_MASK           _U(0x0F)     /**< \brief (ADC_INTENCLR) MASK Register */

#define ADC_INTENSET_OFFSET         0x17         /**< \brief (ADC_INTENSET offset) Interrupt Enable Set */
#define ADC_INTENSET_RESETVALUE     _U(0x00);    /**< \brief (ADC_INTENSET reset_value) Interrupt Enable Set */

#define ADC_INTENSET_RESRDY_Pos     0            /**< \brief (ADC_INTENSET) Result Ready Interrupt Enable */
#define ADC_INTENSET_RESRDY         (_U(0x1) << ADC_INTENSET_RESRDY_Pos)
#define ADC_INTENSET_OVERRUN_Pos    1            /**< \brief (ADC_INTENSET) Overrun Interrupt Enable */
#define ADC_INTENSET_OVERRUN        (_U(0x1) << ADC_INTENSET_OVERRUN_Pos)
#define ADC_INTENSET_WINMON_Pos     2            /**< \brief (ADC_INTENSET) Window Monitor Interrupt Enable */
#define ADC_INTENSET_WINMON         (_U(0x1) << ADC_INTENSET_WINMON_Pos)
#define ADC_INTENSET_SYNCRDY_Pos    3            /**< \brief (ADC_INTENSET) Synchronization Ready Interrupt Enable */
#define ADC_INTENSET_SYNCRDY        (_U(0x1) << ADC_INTENSET_SYNCRDY_Pos)
#define ADC_INTENSET_MASK           _U(0x0F)     /**< \brief (ADC_INTENSET) MASK Register */

#define ADC_INTFLAG_OFFSET          0x18         /**< \brief (ADC_INTFLAG offset) Interrupt Flag Status and Clear */
#define ADC_INTFLAG_RESETVALUE      _U(0x00);    /**< \brief (ADC_INTFLAG reset_value) Interrupt Flag Status and Clear */

#define ADC_INTFLAG_RESRDY_Pos      0            /**< \brief (ADC_INTFLAG) Result Ready */
#define ADC_INTFLAG_RESRDY          (_U(0x1) << ADC_INTFLAG_RESRDY_Pos)
#define ADC_INTFLAG_OVERRUN_Pos     1            /**< \brief (ADC_INTFLAG) Overrun */
#define ADC_INTFLAG_OVERRUN         (_U(0x1) << ADC_INTFLAG_OVERRUN_Pos)
#define ADC_INTFLAG_WINMON_Pos      2            /**< \brief (ADC_INTFLAG) Window Monitor */
#define ADC_INTFLAG_WINMON          (_U(0x1) << ADC_INTFLAG_WINMON_Pos)
#define ADC_INTFLAG_SYNCRDY_Pos     3            /**< \brief (ADC_INTFLAG) Synchronization Ready */
#define ADC_INTFLAG_SYNCRDY         (_U(0x1) << ADC_INTFLAG_SYNCRDY_Pos)
#define ADC_INTFLAG_MASK            _U(0x0F)     /**< \brief (ADC_INTFLAG) MASK Register */

#define ADC_STATUS_OFFSET           0x19         /**< \brief (ADC_STATUS offset) Status */
#define ADC_STATUS_RESETVALUE       _U(0x00);    /**< \brief (ADC_STATUS reset_value) Status */

#define ADC_STATUS_SYNCBUSY_Pos     7            /**< \brief (ADC_STATUS) Synchronization Busy */
#define ADC_STATUS_SYNCBUSY         (_U(0x1) << ADC_STATUS_SYNCBUSY_Pos)
#define ADC_STATUS_MASK             _U(0x80)     /**< \brief (ADC_STATUS) MASK Register */

#define ADC_RESULT_OFFSET           0x1A         /**< \brief (ADC_RESULT offset) Result */
#define ADC_RESULT_RESETVALUE       _U(0x0000);  /**< \brief (ADC_RESULT reset_value) Result */

#define ADC_RESULT_RESULT_Pos       0            /**< \brief (ADC_RESULT) Result Conversion Value */
#define ADC_RESULT_RESULT_Msk       (_U(0xFFFF) << ADC_RESULT_RESULT_Pos)
#define ADC_RESULT_RESULT(value)    (ADC_RESULT_RESULT_Msk & ((value) << ADC_RESULT_RESULT_Pos))
#define ADC_RESULT_MASK             _U(0xFFFF)   /**< \brief (ADC_RESULT) MASK Register */

#define ADC_WINLT_OFFSET            0x1C         /**< \brief (ADC_WINLT offset) Window Monitor Lower Threshold */
#define ADC_WINLT_RESETVALUE        _U(0x0000);  /**< \brief (ADC_WINLT reset_value) Window Monitor Lower Threshold */

#define ADC_WINLT_WINLT_Pos         0            /**< \brief (ADC_WINLT) Window Lower Threshold */
#define ADC_WINLT_WINLT_Msk         (_U(0xFFFF) << ADC_WINLT_WINLT_Pos)
#define ADC_WINLT_WINLT(value)      (ADC_WINLT_WINLT_Msk & ((value) << ADC_WINLT_WINLT_Pos))
#define ADC_WINLT_MASK              _U(0xFFFF)   /**< \brief (ADC_WINLT) MASK Register */

#define ADC_WINUT_OFFSET            0x20         /**< \brief (ADC_WINUT offset) Window Monitor Upper Threshold */
#define ADC_WINUT_RESETVALUE        _U(0x0000);  /**< \brief (ADC_WINUT reset_value) Window Monitor Upper Threshold */

#define ADC_WINUT_WINUT_Pos         0            /**< \brief (ADC_WINUT) Window Upper Threshold */
#define ADC_WINUT_WINUT_Msk         (_U(0xFFFF) << ADC_WINUT_WINUT_Pos)
#define ADC_WINUT_WINUT(value)      (ADC_WINUT_WINUT_Msk & ((value) << ADC_WINUT_WINUT_Pos))
#define ADC_WINUT_MASK              _U(0xFFFF)   /**< \brief (ADC_WINUT) MASK Register */

#define ADC_GAINCORR_OFFSET         0x24         /**< \brief (ADC_GAINCORR offset) Gain Correction */
#define ADC_GAINCORR_RESETVALUE     _U(0x0000);  /**< \brief (ADC_GAINCORR reset_value) Gain Correction */

#define ADC_GAINCORR_GAINCORR_Pos   0            /**< \brief (ADC_GAINCORR) Gain Correction Value */
#define ADC_GAINCORR_GAINCORR_Msk   (_U(0xFFF) << ADC_GAINCORR_GAINCORR_Pos)
#define ADC_GAINCORR_GAINCORR(value) (ADC_GAINCORR_GAINCORR_Msk & ((value) << ADC_GAINCORR_GAINCORR_Pos))
#define ADC_GAINCORR_MASK           _U(0x0FFF)   /**< \brief (ADC_GAINCORR) MASK Register */

#define ADC_OFFSETCORR_OFFSET       0x26         /**< \brief (ADC_OFFSETCORR offset) Offset Correction */
#define ADC_OFFSETCORR_RESETVALUE   _U(0x0000);  /**< \brief (ADC_OFFSETCORR reset_value) Offset Correction */

#define ADC_OFFSETCORR_OFFSETCORR_Pos 0            /**< \brief (ADC_OFFSETCORR) Offset Correction Value */
#define ADC_OFFSETCORR_OFFSETCORR_Msk (_U(0xFFF) << ADC_OFFSETCORR_OFFSETCORR_Pos)
#define ADC_OFFSETCORR_OFFSETCORR(value) (ADC_OFFSETCORR_OFFSETCORR_Msk & ((value) << ADC_OFFSETCORR_OFFSETCORR_Pos))
#define ADC_OFFSETCORR_MASK         _U(0x0FFF)   /**< \brief (ADC_OFFSETCORR) MASK Register */

#define ADC_CALIB_OFFSET            0x28         /**< \brief (ADC_CALIB offset) Calibration */
#define ADC_CALIB_RESETVALUE        _U(0x0000);  /**< \brief (ADC_CALIB reset_value) Calibration */

#define ADC_CALIB_LINEARITY_CAL_Pos 0            /**< \brief (ADC_CALIB) Linearity Calibration Value */
#define ADC_CALIB_LINEARITY_CAL_Msk (_U(0xFF) << ADC_CALIB_LINEARITY_CAL_Pos)
#define ADC_CALIB_LINEARITY_CAL(value) (ADC_CALIB_LINEARITY_CAL_Msk & ((value) << ADC_CALIB_LINEARITY_CAL_Pos))
#define ADC_CALIB_BIAS_CAL_Pos      8            /**< \brief (ADC_CALIB) Bias Calibration Value */
#define ADC_CALIB_BIAS_CAL_Msk      (_U(0x7) << ADC_CALIB_BIAS_CAL_Pos)
#define ADC_CALIB_BIAS_CAL(value)   (ADC_CALIB_BIAS_CAL_Msk & ((value) << ADC_CALIB_BIAS_CAL_Pos))
#define ADC_CALIB_MASK              _U(0x07FF)   /**< \brief (ADC_CALIB) MASK Register */

#define ADC_DBGCTRL_OFFSET          0x2A         /**< \brief (ADC_DBGCTRL offset) Debug Control */
#define ADC_DBGCTRL_RESETVALUE      _U(0x00);    /**< \brief (ADC_DBGCTRL reset_value) Debug Control */

#define ADC_DBGCTRL_DBGRUN_Pos      0            /**< \brief (ADC_DBGCTRL) Debug Run */
#define ADC_DBGCTRL_DBGRUN          (_U(0x1) << ADC_DBGCTRL_DBGRUN_Pos)
#define ADC_DBGCTRL_MASK            _U(0x01)     /**< \brief (ADC_DBGCTRL) MASK Register */

/** \brief ADC hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

typedef struct 
{
	__IO uint8_t	CTRLA;       /**< \brief Offset: 0x00 (R/W  8) Control A */
	__IO uint8_t	REFCTRL;     /**< \brief Offset: 0x01 (R/W  8) Reference Control */
	__IO uint8_t	AVGCTRL;     /**< \brief Offset: 0x02 (R/W  8) Average Control */
	__IO uint8_t	SAMPCTRL;    /**< \brief Offset: 0x03 (R/W  8) Sampling Time Control */
	__IO uint16_t	CTRLB;       /**< \brief Offset: 0x04 (R/W 16) Control B */
		 RoReg8		Reserved1[0x2];
	__IO uint8_t	WINCTRL;     /**< \brief Offset: 0x08 (R/W  8) Window Monitor Control */
		 RoReg8		Reserved2[0x3];
	__IO uint8_t	SWTRIG;      /**< \brief Offset: 0x0C (R/W  8) Software Trigger */
		 RoReg8		Reserved3[0x3];
	__IO uint32_t	INPUTCTRL;   /**< \brief Offset: 0x10 (R/W 32) Inputs Control */
	__IO uint8_t	EVCTRL;      /**< \brief Offset: 0x14 (R/W  8) Event Control */
		 RoReg8		Reserved4[0x1];
	__IO uint8_t	INTENCLR;    /**< \brief Offset: 0x16 (R/W  8) Interrupt Enable Clear */
	__IO uint8_t	INTENSET;    /**< \brief Offset: 0x17 (R/W  8) Interrupt Enable Set */
	__IO uint8_t	INTFLAG;     /**< \brief Offset: 0x18 (R/W  8) Interrupt Flag Status and Clear */
	__I  uint8_t	STATUS;      /**< \brief Offset: 0x19 (R/   8) Status */
	__I  uint16_t	RESULT;      /**< \brief Offset: 0x1A (R/  16) Result */
	__IO uint16_t	WINLT;       /**< \brief Offset: 0x1C (R/W 16) Window Monitor Lower Threshold */
		 RoReg8		Reserved5[0x2];
	__IO uint16_t	WINUT;       /**< \brief Offset: 0x20 (R/W 16) Window Monitor Upper Threshold */
		 RoReg8		Reserved6[0x2];
	__IO uint16_t	GAINCORR;    /**< \brief Offset: 0x24 (R/W 16) Gain Correction */
	__IO uint16_t	OFFSETCORR;  /**< \brief Offset: 0x26 (R/W 16) Offset Correction */
	__IO uint16_t	CALIB;       /**< \brief Offset: 0x28 (R/W 16) Calibration */
	__IO uint8_t	DBGCTRL;     /**< \brief Offset: 0x2A (R/W  8) Debug Control */
} Adc;

#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/*@}*/

#endif /* _SAMD20_ADC_COMPONENT_ */
