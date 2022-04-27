#define I2C_MASTER_SCL_IO             CONFIG_SI7021_I2C_SCL        /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO             CONFIG_SI7021_I2C_SDA        /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM                I2C_NUM_0                /*!< I2C port number for master dev */
#define WRITE_BIT                     0         /*!< I2C master write */
#define READ_BIT                      1         /*!< I2C master read */

#define SI7021_DEFAULT_ADDRESS        0x40      /*!< Default address for SI7021 */
#define SI7021_MEASRH_HOLD_CMD        0xE5      /*!< Measure Relative Humidity, Hold Master Mode */
#define SI7021_READPREVTEMP_CMD       0xE0      /*!< Read Temperature Value from Previous RH Measurement */
   
#define I2C_MASTER_FREQ_HZ            CONFIG_SI7021_I2C_FREQUENCY    /*!< I2C master clock frequency in Hz*/

#define ACK_CHECK_EN                  0x1       /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS                 0x0       /*!< I2C master will not check ack from slave */
#define ACK_VAL                       0x0       /*!< I2C ack value */
#define NACK_VAL                      0x1       /*!< I2C nack value */

float si7021_read_hum(void);
float si7021_read_temp(void);
esp_err_t si7021_i2c_init(void);
