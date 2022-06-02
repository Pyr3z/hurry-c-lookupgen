/*! ***************************************************************************
\ll ** -- FILE DETAILS ----------------------------------------------------- **
\ll ***************************************************************************
    \file     lookupgen.c
    \project  C/C++ SANITIES
    \module   lookupgen
    \author   [Levi Perez](https://leviperez.dev)  \n
    \email    <levi@leviperez.dev>                 \n
    \discord  [Leviathan#2318](https://discordapp.com/channels/@me)
    \copyleft @ref LICENSE (<https://unlicense.org>)
\ll ***************************************************************************
\ll ** -- FILE USAGE ------------------------------------------------------- **
\ll ***************************************************************************
    \brief    --
    \details  --
\ll ***************************************************************************
\ll ** -- DEVELOPMENT HISTORY & ROADMAP ------------------------------------ **
\ll ***************************************************************************
    \version  0.1.0
    \created  2020-02-05 (21:16:23)
******************************************************************************/

/*********************************************************************/
/* PREPROCESSOR */         /* PREPROCESSOR */        /* PREPROCESSOR */
/*********************************************************************/

#include <stdbool.h> /*!< bool true false */
#include <stdio.h>   /*!< printf sprintf fprintf fopen fclose etc */
#include <stdlib.h>  /*!< exit atexit EXIT_SUCCESS EXIT_FAILURE */
#include <assert.h>  /*!< assert static_assert */

#define HURRY_CTZ_SANITY 1
#include "hurry/printbin.h"   /*!< PRINTBIN_BUFFER_32 */
#include "hurry/ctz.h"        /*!< ctz */
#include "hurry/debruijn.h"   /*!< debruijn_01 */
#include "hurry/parsebin.h"   /*!< parsebin8 parsebin16 */
#include "hurry/defcommon.h"  /*!< UNUSED */

/*********************************************************************/
/* TYPEDEFS */               /* PROTOTYPES */             /* GLOBALS */
/*********************************************************************/

typedef enum ERR_
{
  ERR_NONE         = (0 <<  0),
  ERR_FATAL        = (1 << 31),
  ERR_USER_ERROR   = (1 << 30),
  ERR_BAD_MALLOC   = (1 <<  0) | ERR_FATAL,
  ERR_BAD_CLI      = (1 <<  1) | ERR_FATAL | ERR_USER_ERROR,
  ERR_BAD_FILE     = (1 <<  2) | ERR_FATAL,
  ERR_BAD_OPTS     = (1 <<  3) | ERR_USER_ERROR
} ERR_CODE;


static void Global_Init(const char* argv1);
static void Global_Free();
static void Global_Terminate();
static bool Global_HasError(ERR_CODE code);

static struct /* anonymous */
{
  uint32_t          meProblems; /*!< Current error codes passed to Throw(). */
  FILE*             outFile;    /*!< Where to dump the lookup. */
  char              binaryStrBuff [PRINTBIN_MIN_BUFFER_SIZE(uint32_t)];
}
Global =
{
  (uint32_t)ERR_NONE,
  NULL,
  { 0 }
};



/*********************************************************************/
/* FUNCTION */              /* DEFINITIONS */                /* FUN. */
/*********************************************************************/

static bool Global_HasError(ERR_CODE code)
{
  return (Global.meProblems & (uint32_t)code) == (uint32_t)code;
}

static void PrintHelp()
{
  printf("Shit. You need help.\n");
}

static void Global_Free()
{
  if (Global.outFile && Global.outFile != stdout)
  {
    fclose(Global.outFile);
  }

  Global.outFile = NULL;
}

static void Global_Terminate()
{
  Global_Free();
  exit(EXIT_FAILURE);
}

static void Throw(ERR_CODE code, const char* func, unsigned lineno)
{
  static const char* const ERR_TO_STR[] =
  {
    ""/* No detectable errors? I'm commenting myself out then. */"",
    "malloc / calloc failed (you have too many Chrome tabs open m8).",
    "Command line input was poorly designed, so we gave up.",
    "Unable to open the user-provided file name reverting to Stalin-provided.",
    "An invalid test number was passed to the --test (-t) option.",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "⌂THIS⌂⌂⌂⌂bad⌂⌂⌂FUA⌂K⌂⌂",
    "It appears the user has caused some eh, roar.",
    "EVERYONE, THIS IS FATAL. FAT AL, CAN YOU SAY HI TO EVERYONE?"
  };

  static_assert(sizeof(ERR_TO_STR) / sizeof(ERR_TO_STR[0]) == 32, "Count!");

  static const unsigned N_ERR_STRS = (sizeof(ERR_TO_STR) / sizeof(ERR_TO_STR[0]));

  static const char* const EXCEPTION_FORMAT = "<ERR> %s"
                                              "\n      in func  \"%s\""
                                              "\n      on line  #%.4u"
                                              "\n      ERR_CODE %s\n\n";

  if (code)
  {
    unsigned idx = ctz(code);
    Global.meProblems |= code;

    PRINTBIN_BUFFER_32(Global.binaryStrBuff, code);

    if (idx < N_ERR_STRS)
    {
      fprintf(stderr, EXCEPTION_FORMAT, ERR_TO_STR[idx],
                                        func,
                                        lineno,
                                        Global.binaryStrBuff);
    }
    else
    {
      fprintf(stderr, "ABORTING: ctz(%u) returned us %u\n", code, idx);
      Global_Terminate();
    }
  }

  if (Global_HasError(ERR_USER_ERROR))
  {
    PrintHelp();
  }

  if (Global_HasError(ERR_FATAL))
  {
    Global_Terminate();
  }
}

static void Global_Init(const char* argv1)
{
  if (!argv1 || fopen_s(&Global.outFile, argv1, "wb"))
  {
    Global.outFile = stdout;
  }

  if (!Global.outFile)
  {
    Throw(ERR_BAD_FILE, __FUNCTION__, __LINE__);
  }
}



static void FillCTZLookup(unsigned char arr[], unsigned size)
{
  unsigned i;
  for (i = 0; i < size; ++i)
  {
    arr[i] = (unsigned char)ctz(i);
  }
}



static size_t CTZLookup8_Binary()
{
  unsigned char data[0x0100] = { 0 };
  FillCTZLookup(data, 0x0100);

  return fwrite(data, sizeof(unsigned char), 0x0100, Global.outFile);
}

static size_t CTZLookup16_Binary()
{
  unsigned char data[0x010000] = { 0 };
  FillCTZLookup(data, 0x010000);

  return fwrite(data, sizeof(unsigned char), 0x010000, Global.outFile);
}


int main(int argc, const char* const argv[])
{
  /**/ UNUSED(argc);                /**/
  /*   UNUSED(argv);                  */
  /**/ UNUSED(CTZLookup8_Binary);   /**/
  /**/ UNUSED(CTZLookup16_Binary);  /**/

  Global_Init(NULL);

  unsigned bitsize = 8;
  if (argv[1])
  {
    bitsize = (unsigned)atoi(argv[1]);
  }

  if (bitsize == 0)
  {
    unsigned i;
    for (i = 0; i < 64; ++i)
    {
      if (i < 8)
      {
        assert(ctz8((uint8_t)1 << i) == ctz_perfhash8((uint8_t)1 << i));
      }
      if (i < 16)
      {
        assert(ctz16((uint16_t)1 << i) == ctz_perfhash16((uint16_t)1 << i));
      }
      if (i < 32)
      {
        assert(ctz32((uint32_t)1 << i) == ctz_perfhash32((uint32_t)1 << i));
      }

      assert(ctz64((uint64_t)1 << i) == ctz_perfhash64((uint64_t)1 << i));
    }
    puts("YAY! All clear.\n");
  }
  else if (bitsize == 1)
  {
    unsigned t = 1024 * 1024 * 8;
    while (t --> 0)
    {
      hurry_ctz_assert();
    }
  }
  else if (bitsize <= 8)
  {
    uint8_t key8 = debruijn_key8();
    printf("static const uint8_t key8 = 0x%"PRIX8";\n", key8);

    uint_fast8_t lookup8[8] = { 0 };
    uint_fast8_t i, idx;
    for (i = 0; i < 8; ++i)
    {
      idx = ((uint8_t)(key8 * (uint8_t)(1 << i)) >> 5);
      /* printf("%18s : i= %"PRIu8"\n", printbin16((uint16_t)idx), i); */
      assert(idx < 8);
      lookup8[idx] = i;
    }

    printf("static const uint_fast8_t lookup8[8] = { ");
    for (i = 0; i < 8; ++i)
    {
      if (i == 7)
      {
        printf("%"PRIuFAST8" ", lookup8[i]);
      }
      else
      {
        printf("%"PRIuFAST8", ", lookup8[i]);
      }
    }
    printf("};\n");
  }
  else if (bitsize <= 16)
  {
    uint16_t key16 = debruijn_key16();
    printf("static const uint16_t key16 = 0x%"PRIX16";\n", key16);

    uint_fast8_t lookup16[16] = { 0 };
    uint_fast8_t i, idx;
    for (i = 0; i < 16; ++i)
    {
      idx = ((uint16_t)(key16 * (uint16_t)(1 << i)) >> 12);
      assert(idx < 16);
      lookup16[idx] = i;
    }

    printf("static const uint_fast8_t lookup16[16] = { ");
    for (i = 0; i < 16; ++i)
    {
      if (i == 15)
      {
        printf("%"PRIuFAST8" ", lookup16[i]);
      }
      else
      {
        printf("%"PRIuFAST8", ", lookup16[i]);
      }
    }
    printf("};\n");
  }
  else if (bitsize <= 32)
  {
    uint32_t key32 = debruijn_key32();
    printf("static const uint32_t key32 = 0x%"PRIX32";\n", key32);

    uint_fast8_t lookup32[32] = { 0 };
    uint_fast8_t i, idx;
    for (i = 0; i < 32; ++i)
    {
      idx = (uint32_t)((key32 * ((uint32_t)1 << i))) >> 27;
      assert(idx < 32);
      lookup32[idx] = i;
    }

    printf("static const uint_fast8_t lookup32[32] = { ");
    for (i = 0; i < 32; ++i)
    {
      if (i == 31)
      {
        printf("%"PRIuFAST8" ", lookup32[i]);
      }
      else
      {
        printf("%"PRIuFAST8", ", lookup32[i]);
      }
    }
    printf("};\n");
  }
  else if (bitsize <= 64)
  {
    uint64_t key64 = debruijn_key64();
    printf("static const uint64_t key64 = 0x%"PRIX64";\n", key64);

    uint_fast8_t lookup64[64] = { 0 };
    uint_fast8_t i, idx;
    for (i = 0; i < 64; ++i)
    {
      idx = ((uint64_t)(key64 * ((uint64_t)1 << i)) >> 58);
      assert(idx < 64);
      lookup64[idx] = i;
    }

    printf("static const uint_fast8_t lookup64[64] = { ");
    for (i = 0; i < 64; ++i)
    {
      if (i == 63)
      {
        printf("%"PRIuFAST8" ", lookup64[i]);
      }
      else
      {
        printf("%"PRIuFAST8", ", lookup64[i]);
      }
    }
    printf("};\n");
  }
  else
  {
    assert(false);
  }

/*
  unsigned n = 1024 * 1024 * 8;

  while (n --> 0)
  {
    hurry_ctz_assert();
  }
*/
/*
  if (!CTZLookup16_Binary())
  {
    Throw(ERR_FATAL, __FUNCTION__, __LINE__);
    Global_Terminate();
  }
*/

  Global_Free();
  return EXIT_SUCCESS;
}


