/*
 * Author: Brendan Le Foll <brendan.le.foll@intel.com>
 * Copyright (c) 2014 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "pwm.h"
#include <stdexcept>

namespace mraa {

/**
 * @brief API to Pulse Width Modulation
 *
 * This file defines the PWM interface for libmraa
 *
 * @snippet Pwm3-cycle.cpp Interesting
 */
class Pwm {
    public:
        /**
         * instanciates a PWM object on a pin
         *
         * @param pin the pin number used on your board
         * @param owner if you are the owner of the pin the destructor will
         * @param chipid the pwmchip to use, use only in raw mode
         * unexport the pin from sysfs, default behaviour is you are the owner
         * if the pinmapper exported it
         */
        Pwm(int pin, bool owner=true, int chipid=-1) {
            if (chipid == -1) {
                m_pwm = mraa_pwm_init(pin);
            }
            else {
                m_pwm = mraa_pwm_init_raw(pin, chipid);
            }

            if (m_pwm == NULL) {
                throw std::invalid_argument("Error initialising PWM on pin");
            }

            if (!owner) {
                mraa_pwm_owner(m_pwm, 0);
            }
        }
        /**
         * Pwm destructor
         */
        ~Pwm() {
            mraa_pwm_close(m_pwm);
        }
        /**
         * Set the output duty-cycle percentage, as a float
         *
         * @param percentage A floating-point value representing percentage of
         * output. The value should lie between 0.0f (representing on 0%) and
         * 1.0f Values above or below this range will be set at either 0.0f or
         * 1.0f
         * @return Result of operation
         */
        mraa_result_t write(float percentage) {
            return mraa_pwm_write(m_pwm, percentage);
        }
        /**
         * Read the ouput duty-cycle percentage, as a float
         *
         * @return A floating-point value representing percentage of
         * output. The value should lie between 0.0f (representing on 0%) and
         * 1.0f Values above or below this range will be set at either 0.0f or
         * 1.0f
         */
        float read() {
            return mraa_pwm_read(m_pwm);
        }
        /**
         * Set the PWM period as seconds represented in a float
         *
         * @param period Period represented as a float in seconds
         * @return Result of operation
         */
        mraa_result_t period(float period) {
            return mraa_pwm_period(m_pwm, period);
        }
        /**
         * Set period, milliseconds
         *
         * @param ms milliseconds for period
         * @return Result of operation
         */
        mraa_result_t period_ms(int ms) {
            return mraa_pwm_period_ms(m_pwm, ms);
        }
        /**
         * Set period, microseconds
         *
         * @param us microseconds as period
         * @return Result of operation
         */
        mraa_result_t period_us(int us) {
            return mraa_pwm_period_us(m_pwm, us);
        }
        /**
         * Set pulsewidth, As represnted by seconds in a (float)
         *
         * @param seconds The duration of a pulse
         * @return Result of operation
         */
        mraa_result_t pulsewidth(float seconds) {
            return mraa_pwm_pulsewidth(m_pwm, seconds);
        }
        /**
         * Set pulsewidth, milliseconds
         *
         * @param ms milliseconds for pulsewidth
         * @return Result of operation
         */
        mraa_result_t pulsewidth_ms(int ms) {
            return mraa_pwm_pulsewidth_ms(m_pwm, ms);
        }
        /**
         * The pulsewidth, microseconds
         *
         * @param us microseconds for pulsewidth
         * @return Result of operation
         */
        mraa_result_t pulsewidth_us(int us) {
            return mraa_pwm_pulsewidth_us(m_pwm, us);
        }
        /**
         * Set the enable status of the PWM pin. None zero will assume on with
         * output being driven and 0 will disable the output
         *
         * @param enable enable status of pin
         * @return Result of operation
         */
        mraa_result_t enable(bool enable) {
            if (enable)
                return mraa_pwm_enable(m_pwm, 1);
            else
                return mraa_pwm_enable(m_pwm, 0);
        }
        /**
         * Set the period and duty of a PWM object.
         *
         * @param period represented in ms.
         * @param duty represnted in ms as float.
         * @return Result of operation
         */
        mraa_result_t config_ms(int period, float duty) {
            return mraa_pwm_config_ms(m_pwm, period, duty);
        }
        /**
         * Set the period and duty (percent) of a PWM object.
         *
         * @param period as represented in ms.
         * @param duty percentage i.e. 50% = 0.5f
         * @return Result of operation
         */
        mraa_result_t config_percent(int period, float duty) {
            return mraa_pwm_config_percent(m_pwm, period, duty);
        }

    private:
        mraa_pwm_context m_pwm;
};

}
