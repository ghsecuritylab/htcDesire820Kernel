// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_INSTALLER_UTIL_INSTALLATION_VALIDATOR_H_
#define CHROME_INSTALLER_UTIL_INSTALLATION_VALIDATOR_H_

#include <map>
#include <set>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/strings/string16.h"
#include "chrome/installer/util/browser_distribution.h"

class CommandLine;

namespace base {
class FilePath;
}

namespace installer {

class InstallationState;
class AppCommand;
class ProductState;

class InstallationValidator {
 public:
  class ProductBits {
   public:
    
    enum {
      CHROME_SINGLE           = 0x01,
      CHROME_MULTI            = 0x02,
      CHROME_FRAME_SINGLE     = 0x04,
      CHROME_FRAME_MULTI      = 0x08,
      CHROME_APP_HOST         = 0x10,
    };
  };  

  
  enum InstallationType {
    NO_PRODUCTS = 0,
    CHROME_SINGLE =
        ProductBits::CHROME_SINGLE,
    CHROME_MULTI =
        ProductBits::CHROME_MULTI,
    CHROME_FRAME_SINGLE =
        ProductBits::CHROME_FRAME_SINGLE,
    CHROME_FRAME_SINGLE_CHROME_SINGLE =
        ProductBits::CHROME_FRAME_SINGLE | ProductBits::CHROME_SINGLE,
    CHROME_FRAME_SINGLE_CHROME_MULTI =
        ProductBits::CHROME_FRAME_SINGLE | ProductBits::CHROME_MULTI,
    CHROME_FRAME_MULTI =
        ProductBits::CHROME_FRAME_MULTI,
    CHROME_FRAME_MULTI_CHROME_MULTI =
        ProductBits::CHROME_FRAME_MULTI | ProductBits::CHROME_MULTI,
    CHROME_APP_HOST =
        ProductBits::CHROME_APP_HOST,
    CHROME_APP_HOST_CHROME_FRAME_SINGLE =
        ProductBits::CHROME_APP_HOST | ProductBits::CHROME_FRAME_SINGLE,
    CHROME_APP_HOST_CHROME_FRAME_SINGLE_CHROME_MULTI =
        ProductBits::CHROME_APP_HOST | ProductBits::CHROME_FRAME_SINGLE |
        ProductBits::CHROME_MULTI,
    CHROME_APP_HOST_CHROME_FRAME_MULTI =
        ProductBits::CHROME_APP_HOST | ProductBits::CHROME_FRAME_MULTI,
    CHROME_APP_HOST_CHROME_FRAME_MULTI_CHROME_MULTI =
        ProductBits::CHROME_APP_HOST | ProductBits::CHROME_FRAME_MULTI |
        ProductBits::CHROME_MULTI,
    CHROME_APP_HOST_CHROME_MULTI =
        ProductBits::CHROME_APP_HOST | ProductBits::CHROME_MULTI,
  };

  
  
  
  static bool ValidateInstallationTypeForState(
      const InstallationState& machine_state,
      bool system_level,
      InstallationType* type);

  
  
  static bool ValidateInstallationType(bool system_level,
                                       InstallationType* type);

 protected:
  struct ProductContext;
  typedef std::vector<std::pair<std::string, bool> > SwitchExpectations;
  typedef void (*CommandValidatorFn)(const ProductContext& ctx,
                                     const AppCommand& app_cmd,
                                     bool* is_valid);
  typedef std::map<string16, CommandValidatorFn> CommandExpectations;

  
  class ProductRules {
   public:
    virtual ~ProductRules() { }
    virtual BrowserDistribution::Type distribution_type() const = 0;
    virtual void AddUninstallSwitchExpectations(
        const ProductContext& ctx,
        SwitchExpectations* expectations) const = 0;
    virtual void AddRenameSwitchExpectations(
        const ProductContext& ctx,
        SwitchExpectations* expectations) const = 0;
    
    virtual bool UsageStatsAllowed(const ProductContext& ctx) const = 0;
  };

  
  class ChromeRules : public ProductRules {
   public:
    virtual BrowserDistribution::Type distribution_type() const OVERRIDE;
    virtual void AddUninstallSwitchExpectations(
        const ProductContext& ctx,
        SwitchExpectations* expectations) const OVERRIDE;
    virtual void AddRenameSwitchExpectations(
        const ProductContext& ctx,
        SwitchExpectations* expectations) const OVERRIDE;
    virtual bool UsageStatsAllowed(const ProductContext& ctx) const OVERRIDE;
  };

  
  class ChromeFrameRules : public ProductRules {
   public:
    virtual BrowserDistribution::Type distribution_type() const OVERRIDE;
    virtual void AddUninstallSwitchExpectations(
        const ProductContext& ctx,
        SwitchExpectations* expectations) const OVERRIDE;
    virtual void AddRenameSwitchExpectations(
        const ProductContext& ctx,
        SwitchExpectations* expectations) const OVERRIDE;
    virtual bool UsageStatsAllowed(const ProductContext& ctx) const OVERRIDE;
  };

  
  class ChromeAppHostRules : public ProductRules {
   public:
    virtual BrowserDistribution::Type distribution_type() const OVERRIDE;
    virtual void AddUninstallSwitchExpectations(
        const ProductContext& ctx,
        SwitchExpectations* expectations) const OVERRIDE;
    virtual void AddRenameSwitchExpectations(
        const ProductContext& ctx,
        SwitchExpectations* expectations) const OVERRIDE;
    virtual bool UsageStatsAllowed(const ProductContext& ctx) const OVERRIDE;
  };

  
  class ChromeBinariesRules : public ProductRules {
   public:
    virtual BrowserDistribution::Type distribution_type() const OVERRIDE;
    virtual void AddUninstallSwitchExpectations(
        const ProductContext& ctx,
        SwitchExpectations* expectations) const OVERRIDE;
    virtual void AddRenameSwitchExpectations(
        const ProductContext& ctx,
        SwitchExpectations* expectations) const OVERRIDE;
    virtual bool UsageStatsAllowed(const ProductContext& ctx) const OVERRIDE;
  };

  struct ProductContext {
    ProductContext(const InstallationState& machine_state_in,
                   bool system_install_in,
                   const ProductState& state_in,
                   const ProductRules& rules_in)
        : machine_state(machine_state_in),
          system_install(system_install_in),
          dist(BrowserDistribution::GetSpecificDistribution(
              rules_in.distribution_type())),
          state(state_in),
          rules(rules_in) {
    }

    const InstallationState& machine_state;
    bool system_install;
    BrowserDistribution* dist;
    const ProductState& state;
    const ProductRules& rules;
  };

  
  
  
  static void ValidateAppCommandFlags(const ProductContext& ctx,
                                      const AppCommand& app_cmd,
                                      const std::set<string16>& flags_expected,
                                      const string16& name,
                                      bool* is_valid);
  static void ValidateInstallCommand(const ProductContext& ctx,
                                     const AppCommand& app_cmd,
                                     const wchar_t* expected_command,
                                     const wchar_t* expected_app_name,
                                     const char* expected_switch,
                                     bool* is_valid);
  static void ValidateInstallAppCommand(const ProductContext& ctx,
                                        const AppCommand& app_cmd,
                                        bool* is_valid);
  static void ValidateInstallExtensionCommand(const ProductContext& ctx,
                                              const AppCommand& app_cmd,
                                              bool* is_valid);
  static void ValidateOnOsUpgradeCommand(const ProductContext& ctx,
                                         const AppCommand& app_cmd,
                                         bool* is_valid);
  static void ValidateQueryEULAAcceptanceCommand(const ProductContext& ctx,
                                                 const AppCommand& app_cmd,
                                                 bool* is_valid);
  static void ValidateQuickEnableApplicationHostCommand(
    const ProductContext& ctx,
    const AppCommand& app_cmd,
    bool* is_valid);

  static void ValidateAppCommandExpectations(
      const ProductContext& ctx,
      const CommandExpectations& expectations,
      bool* is_valid);
  static void ValidateBinariesCommands(const ProductContext& ctx,
                                       bool* is_valid);
  static void ValidateBinaries(const InstallationState& machine_state,
                               bool system_install,
                               const ProductState& binaries_state,
                               bool* is_valid);
  static void ValidateSetupPath(const ProductContext& ctx,
                                const base::FilePath& setup_exe,
                                const string16& purpose,
                                bool* is_valid);
  static void ValidateCommandExpectations(const ProductContext& ctx,
                                          const CommandLine& command,
                                          const SwitchExpectations& expected,
                                          const string16& source,
                                          bool* is_valid);
  static void ValidateUninstallCommand(const ProductContext& ctx,
                                       const CommandLine& command,
                                       const string16& source,
                                       bool* is_valid);
  static void ValidateRenameCommand(const ProductContext& ctx,
                                    bool* is_valid);
  static void ValidateOldVersionValues(const ProductContext& ctx,
                                       bool* is_valid);
  static void ValidateMultiInstallProduct(const ProductContext& ctx,
                                          bool* is_valid);
  static void ValidateAppCommands(const ProductContext& ctx,
                                  bool* is_valid);
  static void ValidateUsageStats(const ProductContext& ctx,
                                 bool* is_valid);
  static void ValidateProduct(const InstallationState& machine_state,
                              bool system_install,
                              const ProductState& product_state,
                              const ProductRules& rules,
                              bool* is_valid);

  
  static const InstallationType kInstallationTypes[];

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(InstallationValidator);
};

}  

#endif  