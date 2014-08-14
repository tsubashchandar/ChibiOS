/*
    ChibiOS/HAL - Copyright (C) 2006-2014 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
/*
   Concepts and parts of this file have been contributed by Uladzimir Pylinsky
   aka barthess.
 */

/**
 * @file    fsmc.h
 * @brief   FSMC Driver subsystem low level driver header template.
 *
 * @addtogroup FSMC
 * @{
 */


#ifndef _FSMC_H_
#define _FSMC_H_

#if HAL_USE_NAND || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * Base bank mappings
 */
#define FSMC_Bank1_MAP_BASE               ((uint32_t) 0x60000000)
#define FSMC_Bank2_MAP_BASE               ((uint32_t) 0x70000000)
#define FSMC_Bank3_MAP_BASE               ((uint32_t) 0x80000000)
#define FSMC_Bank4_MAP_BASE               ((uint32_t) 0x90000000)

/*
 * Bank 2 (NAND)
 */
#define FSMC_Bank2_MAP_COMMON             (FSMC_Bank2_MAP_BASE + 0)
#define FSMC_Bank2_MAP_ATTR               (FSMC_Bank2_MAP_BASE + 0x8000000)

#define FSMC_Bank2_MAP_COMMON_DATA        (FSMC_Bank2_MAP_COMMON + 0)
#define FSMC_Bank2_MAP_COMMON_CMD         (FSMC_Bank2_MAP_COMMON + 0x10000)
#define FSMC_Bank2_MAP_COMMON_ADDR        (FSMC_Bank2_MAP_COMMON + 0x20000)

#define FSMC_Bank2_MAP_ATTR_DATA          (FSMC_Bank2_MAP_ATTR + 0)
#define FSMC_Bank2_MAP_ATTR_CMD           (FSMC_Bank2_MAP_ATTR + 0x10000)
#define FSMC_Bank2_MAP_ATTR_ADDR          (FSMC_Bank2_MAP_ATTR + 0x20000)

/*
 * Bank 3 (NAND)
 */
#define FSMC_Bank3_MAP_COMMON             (FSMC_Bank3_MAP_BASE + 0)
#define FSMC_Bank3_MAP_ATTR               (FSMC_Bank3_MAP_BASE + 0x8000000)

#define FSMC_Bank3_MAP_COMMON_DATA        (FSMC_Bank3_MAP_COMMON + 0)
#define FSMC_Bank3_MAP_COMMON_CMD         (FSMC_Bank3_MAP_COMMON + 0x10000)
#define FSMC_Bank3_MAP_COMMON_ADDR        (FSMC_Bank3_MAP_COMMON + 0x20000)

#define FSMC_Bank3_MAP_ATTR_DATA          (FSMC_Bank3_MAP_ATTR + 0)
#define FSMC_Bank3_MAP_ATTR_CMD           (FSMC_Bank3_MAP_ATTR + 0x10000)
#define FSMC_Bank3_MAP_ATTR_ADDR          (FSMC_Bank3_MAP_ATTR + 0x20000)

/*
 * Bank 4 (PC card)
 */
#define FSMC_Bank4_MAP_COMMON             (FSMC_Bank4_MAP_BASE + 0)
#define FSMC_Bank4_MAP_ATTR               (FSMC_Bank4_MAP_BASE + 0x8000000)
#define FSMC_Bank4_MAP_IO                 (FSMC_Bank4_MAP_BASE + 0xC000000)

/*
 * More convenient typedefs than CMSIS has
 */
typedef struct {
  __IO uint32_t PCR;        /**< NAND Flash control */
  __IO uint32_t SR;         /**< NAND Flash FIFO status and interrupt */
  __IO uint32_t PMEM;       /**< NAND Flash Common memory space timing */
  __IO uint32_t PATT;       /**< NAND Flash Attribute memory space timing  */
  uint32_t      RESERVED0;  /**< Reserved, 0x70     */
  __IO uint32_t ECCR;       /**< NAND Flash ECC result registers */
} FSMC_NAND_TypeDef;

typedef struct {
  __IO uint32_t PCR;       /**< PC Card  control */
  __IO uint32_t SR;        /**< PC Card  FIFO status and interrupt */
  __IO uint32_t PMEM;      /**< PC Card  Common memory space timing */
  __IO uint32_t PATT;      /**< PC Card  Attribute memory space timing */
  __IO uint32_t PIO;       /**< PC Card  I/O space timing */
} FSMC_PCCard_TypeDef;

/**
 * @brief   PCR register
 */
#define  FSMC_PCR_PWAITEN         ((uint32_t)0x00000002)
#define  FSMC_PCR_PBKEN           ((uint32_t)0x00000004)
#define  FSMC_PCR_PTYP            ((uint32_t)0x00000008)
#define  FSMC_PCR_ECCEN           ((uint32_t)0x00000040)
#define  FSMC_PCR_PTYP_PCCARD     0
#define  FSMC_PCR_PTYP_NAND       FSMC_PCR_PTYP

/**
 * @brief   SR register
 */
#define  FSMC_SR_IRS              ((uint8_t)0x01)
#define  FSMC_SR_ILS              ((uint8_t)0x02)
#define  FSMC_SR_IFS              ((uint8_t)0x04)
#define  FSMC_SR_IREN             ((uint8_t)0x08)
#define  FSMC_SR_ILEN             ((uint8_t)0x10)
#define  FSMC_SR_IFEN             ((uint8_t)0x20)
#define  FSMC_SR_FEMPT            ((uint8_t)0x40)
#define  FSMC_SR_ISR_MASK         (FSMC_SR_IRS | FSMC_SR_ILS | FSMC_SR_IFS)

/**
 * @brief   RCR register
 */
#define  FSMC_BCR_MBKEN           ((uint32_t)0x00000001)
#define  FSMC_BCR_MUXEN           ((uint32_t)0x00000002)
#define  FSMC_BCR_FACCEN          ((uint32_t)0x00000040)
#define  FSMC_BCR_BURSTEN         ((uint32_t)0x00000100)
#define  FSMC_BCR_WAITPOL         ((uint32_t)0x00000200)
#define  FSMC_BCR_WRAPMOD         ((uint32_t)0x00000400)
#define  FSMC_BCR_WAITCFG         ((uint32_t)0x00000800)
#define  FSMC_BCR_WREN            ((uint32_t)0x00001000)
#define  FSMC_BCR_WAITEN          ((uint32_t)0x00002000)
#define  FSMC_BCR_EXTMOD          ((uint32_t)0x00004000)
#define  FSMC_BCR_ASYNCWAIT       ((uint32_t)0x00008000)
#define  FSMC_BCR_CBURSTRW        ((uint32_t)0x00080000)

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   FSMC driver enable switch.
 * @details If set to @p TRUE the support for FSMC is included.
 */
#if !defined(STM32_FSMC_USE_FSMC1) || defined(__DOXYGEN__)
#define STM32_FSMC_USE_FSMC1             FALSE
#endif

/**
 * @brief   Internal FSMC interrupt enable switch
 * @details MCUs in 100-pin package has no dedicated interrupt pin for FSMC.
 *          You have to use EXTI module instead to workaround this issue.
 */
#if !defined(STM32_NAND_USE_EXT_INT) || defined(__DOXYGEN__)
#define STM32_NAND_USE_EXT_INT          FALSE
#endif

/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/
#if !STM32_FSMC_USE_FSMC1
#error "FSMC driver activated but no FSMC peripheral assigned"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a structure representing an FSMC driver.
 */
typedef struct FSMCDriver FSMCDriver;

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
  FSMC_UNINIT = 0,                   /**< Not initialized.                   */
  FSMC_STOP = 1,                     /**< Stopped.                           */
  FSMC_READY = 2,                    /**< Ready.                             */
} fsmcstate_t;

/**
 * @brief   Driver configuration structure.
 * @note    Empty on this architecture.
 */
typedef struct {

} FSMCConfig;

/**
 * @brief   Structure representing an FSMC driver.
 */
struct FSMCDriver {
  /**
   * @brief Driver state.
   */
  fsmcstate_t               state;
  /* End of the mandatory fields.*/
#if STM32_NAND_USE_FSMC_NAND1
  FSMC_NAND_TypeDef         *nand1;
#endif
#if STM32_NAND_USE_FSMC_NAND2
  FSMC_NAND_TypeDef         *nand2;
#endif
#if STM32_USE_FSMC_PCCARD
  FSMC_PCCard_TypeDef       *pccard;
#endif
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if STM32_FSMC_USE_FSMC1 && !defined(__DOXYGEN__)
extern FSMCDriver FSMCD1;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void fsmc_init(void);
  void fsmc_start(FSMCDriver *fsmcp);
  void fsmc_stop(FSMCDriver *fsmcp);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_NAND */

#endif /* _FSMC_H_ */

/** @} */
