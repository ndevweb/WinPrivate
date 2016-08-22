{$IFNDEF COMPINFOS_INC}
{$DEFINE COMPINFOS_INC}

{$DEFINE BORLAND}

{ Set FreePascal to Delphi mode }
{$IFDEF FPC}
  {$MODE DELPHI}
  {$ASMMODE Intel}
  {$UNDEF BORLAND}
  {$DEFINE CPUASM}
   // FPC defines CPU32, CPU64 and Unix automatically
{$ENDIF}

{$IFDEF BORLAND}
  {$IFDEF LINUX}
    {$DEFINE KYLIX}
  {$ENDIF LINUX}
  {$IFNDEF CLR}
    {$IFNDEF CPUX86}
      // CPUX86 is not defined, which means it most likely is a 64 bits compiler.
      // However, this is only the case if either of two other symbols are defined:
      // http://docwiki.embarcadero.com/RADStudio/Seattle/en/Conditional_compilation_%28Delphi%29
      {$DEFINE CPU64}
      {$DEFINE DELPHI64_TEMPORARY}
      {$IFNDEF CPUX64}
        {$IFNDEF CPU64BITS}
          {$DEFINE CPU386}  // None of the two 64-bits symbols are defined, assume this is 32-bit
          {$DEFINE CPU32}   
          {$UNDEF CPU64}
          {$UNDEF DELPHI64_TEMPORARY}
        {$ENDIF ~CPU64BITS}
      {$ENDIF ~CPUX64}
    {$ELSE ~CPUX86}
      {$DEFINE CPU386}
      {$DEFINE CPU32}
    {$ENDIF ~CPUX86}

    // The ASSEMBLER symbol appeared with Delphi 7
    {$IFNDEF COMPILER7_UP}
      {$DEFINE CPUASM}
    {$ELSE}
      {$IFDEF ASSEMBLER}
        {$DEFINE CPUASM}
      {$ENDIF ASSEMBLER}
    {$ENDIF ~COMPILER7_UP}    
  {$ENDIF ~CLR}
{$ENDIF BORLAND}

{------------------------------------------------------------------------------}
{ VERXXX to COMPILERX, DELPHIX and BCBX mappings                               }
{------------------------------------------------------------------------------}

{$IFDEF BORLAND}
  {$IFDEF KYLIX}
            //
            // This is FPC-incompatible code and was excluded from jedi.inc for this reason
            //
            // Kylix 3/C++ for some reason evaluates CompilerVersion comparisons to False,
            // if the constant to compare with is a floating point value - weird.
            // The "+" sign prevents Kylix/Delphi from issueing a warning about comparing
            // signed and unsigned values.
            //
                {$IF not Declared(CompilerVersion)}
                  {$DEFINE KYLIX1}
                  {$DEFINE COMPILER6}
                  {$DEFINE DELPHICOMPILER6}
                  {$DEFINE RTL140_UP}
                {$ELSEIF Declared(CompilerVersion) and (CompilerVersion > +14)}
                  {$DEFINE KYLIX2}
                  {$DEFINE COMPILER6}
                  {$DEFINE DELPHICOMPILER6}
                  {$DEFINE RTL142_UP}
                {$ELSEIF Declared(CompilerVersion) and (CompilerVersion < +15)}
                  {$DEFINE KYLIX3}
                  {$DEFINE COMPILER6}
                  {$IFNDEF BCB}
                    {$DEFINE DELPHICOMPILER6}
                  {$ENDIF}
                  {$DEFINE RTL145_UP}
                {$ELSE}
                  Add new Kylix version
            {$IFEND}
  {$ELSE ~KYLIX}

{$DEFINE UNKNOWN_COMPILER_VERSION}

(* BEGIN Delphi 1 *)
  {$IFDEF VER80}
      {$DEFINE COMPILER1}
      {$DEFINE DELPHI1}
      {$DEFINE DELPHICOMPILER1}
      {$DEFINE RTL80_UP}
      {$UNDEF UNKNOWN_COMPILER_VERSION}
  {$ENDIF}
(* END Delphi 1 *)

  {$ENDIF ~KYLIX}

  {$IFDEF BCB}
    {$DEFINE CPPBUILDER}
    {$DEFINE BCBCOMPILER}
  {$ELSE ~BCB}
    {$DEFINE DELPHI}
    {$DEFINE DELPHICOMPILER}
  {$ENDIF ~BCB}

{$ENDIF BORLAND}

{------------------------------------------------------------------------------}
{ Map COMPILERX_UP to friendly feature names                                   }
{------------------------------------------------------------------------------}

{$IFDEF FPC}
  {$IFDEF  VER1_0}
     Please use FPC 2.0 or higher to compile this.
  {$ELSE}
    {$DEFINE SUPPORTS_OUTPARAMS}
    {$DEFINE SUPPORTS_WIDECHAR}
    {$DEFINE SUPPORTS_WIDESTRING}
    {$IFDEF HASINTF}
      {$DEFINE SUPPORTS_INTERFACE}
    {$ENDIF}
    {$IFDEF HASVARIANT}
      {$DEFINE SUPPORTS_VARIANT}
    {$ENDIF}
    {$IFDEF FPC_HAS_TYPE_SINGLE}
      {$DEFINE SUPPORTS_SINGLE}
    {$ENDIF}
    {$IFDEF FPC_HAS_TYPE_DOUBLE}
      {$DEFINE SUPPORTS_DOUBLE}
    {$ENDIF}
    {$IFDEF FPC_HAS_TYPE_EXTENDED}
      {$DEFINE SUPPORTS_EXTENDED}
    {$ENDIF}
    {$IFDEF HASCURRENCY}
      {$DEFINE SUPPORTS_CURRENCY}
    {$ENDIF}
    {$DEFINE SUPPORTS_THREADVAR}
    {$DEFINE SUPPORTS_CONSTPARAMS}
    {$DEFINE SUPPORTS_LONGWORD}
    {$DEFINE SUPPORTS_INT64}
    {$DEFINE SUPPORTS_DYNAMICARRAYS}
    {$DEFINE SUPPORTS_DEFAULTPARAMS}
    {$DEFINE SUPPORTS_OVERLOAD}
    {$DEFINE ACCEPT_DEPRECATED}  // 2.2 also gives warnings
    {$DEFINE ACCEPT_PLATFORM}    // 2.2 also gives warnings
    {$DEFINE ACCEPT_LIBRARY}
    {$DEFINE SUPPORTS_EXTSYM}
    {$DEFINE SUPPORTS_NODEFINE}

    {$DEFINE SUPPORTS_CUSTOMVARIANTS}
    {$DEFINE SUPPORTS_VARARGS}
    {$DEFINE SUPPORTS_ENUMVALUE}
    {$IFDEF LINUX}
      {$DEFINE HAS_UNIT_LIBC}
    {$ENDIF LINUX}
    {$DEFINE HAS_UNIT_CONTNRS}
    {$DEFINE HAS_UNIT_TYPES}
    {$DEFINE HAS_UNIT_VARIANTS}
    {$DEFINE HAS_UNIT_STRUTILS}
    {$DEFINE HAS_UNIT_DATEUTILS}
    {$DEFINE HAS_UNIT_RTLCONSTS}

    {$DEFINE XPLATFORM_RTL}

    {$IFDEF VER2_2}
      {$DEFINE SUPPORTS_DISPINTERFACE}
      {$DEFINE SUPPORTS_IMPLEMENTS}
      {$DEFINE SUPPORTS_DISPID}
    {$ELSE}
      {$UNDEF SUPPORTS_DISPINTERFACE}
      {$UNDEF SUPPORTS_IMPLEMENTS}
    {$endif}
    {$UNDEF SUPPORTS_UNSAFE_WARNINGS}
  {$ENDIF}
{$ENDIF FPC}

{$IFDEF CLR}
  {$DEFINE SUPPORTS_UNICODE}
{$ENDIF CLR}

{$IFDEF COMPILER1_UP}
  {$DEFINE SUPPORTS_CONSTPARAMS}
  {$DEFINE SUPPORTS_SINGLE}
  {$DEFINE SUPPORTS_DOUBLE}
  {$DEFINE SUPPORTS_EXTENDED}
  {$DEFINE SUPPORTS_PACKAGES} 
{$ENDIF COMPILER1_UP}


{------------------------------------------------------------------------------}
{ Cross-platform related defines                                               }
{------------------------------------------------------------------------------}

{$IFNDEF CPUASM}
  {$DEFINE PUREPASCAL}
{$ENDIF ~CPUASM}

{$IFDEF WIN32}
  {$DEFINE MSWINDOWS} // predefined for D6+/BCB6+
  {$DEFINE Win32API}
{$ENDIF}

{$IFDEF DELPHILANGUAGE}
  {$IFDEF LINUX}
    {$DEFINE UNIX}
  {$ENDIF}

  {$IFNDEF CONSOLE}
    {$IFDEF LINUX}
      {$DEFINE VisualCLX}
    {$ENDIF}
    {$IFNDEF VisualCLX}
      {$DEFINE VCL}
    {$ENDIF}
  {$ENDIF ~CONSOLE}
{$ENDIF DELPHILANGUAGE}

{------------------------------------------------------------------------------}
{ Compiler settings                                                            }
{------------------------------------------------------------------------------}

{$IFOPT A+} {$DEFINE ALIGN_ON} {$ENDIF}
{$IFOPT B+} {$DEFINE BOOLEVAL_ON} {$ENDIF}
{$IFDEF COMPILER2_UP}
  {$IFOPT C+} {$DEFINE ASSERTIONS_ON} {$ENDIF}
{$ENDIF}
{$IFOPT D+} {$DEFINE DEBUGINFO_ON} {$ENDIF}
{$IFOPT G+} {$DEFINE IMPORTEDDATA_ON} {$ENDIF}
{$IFDEF COMPILER2_UP}
  {$IFOPT H+} {$DEFINE LONGSTRINGS_ON} {$ENDIF}
{$ENDIF}

// Hints
{$IFOPT I+} {$DEFINE IOCHECKS_ON} {$ENDIF}
{$IFDEF COMPILER2_UP}
  {$IFOPT J+} {$DEFINE WRITEABLECONST_ON} {$ENDIF}
{$ENDIF}
{$IFOPT L+} {$DEFINE LOCALSYMBOLS} {$DEFINE LOCALSYMBOLS_ON} {$ENDIF}
{$IFOPT M+} {$DEFINE TYPEINFO_ON} {$ENDIF}
{$IFOPT O+} {$DEFINE OPTIMIZATION_ON} {$ENDIF}
{$IFOPT P+} {$DEFINE OPENSTRINGS_ON} {$ENDIF}
{$IFOPT Q+} {$DEFINE OVERFLOWCHECKS_ON} {$ENDIF}
{$IFOPT R+} {$DEFINE RANGECHECKS_ON} {$ENDIF}

// Real compatibility
{$IFOPT T+} {$DEFINE TYPEDADDRESS_ON} {$ENDIF}
{$IFOPT U+} {$DEFINE SAFEDIVIDE_ON} {$ENDIF}
{$IFOPT V+} {$DEFINE VARSTRINGCHECKS_ON} {$ENDIF}
{$IFOPT W+} {$DEFINE STACKFRAMES_ON} {$ENDIF}

// Warnings
{$IFOPT X+} {$DEFINE EXTENDEDSYNTAX_ON} {$ENDIF}

// for Delphi/BCB trial versions remove the point from the line below
{.$UNDEF SUPPORTS_WEAKPACKAGEUNIT}

{$ENDIF ~COMPINFOS_INC}
