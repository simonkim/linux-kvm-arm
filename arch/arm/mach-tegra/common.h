struct arm_soc_desc;
extern struct arm_soc_desc tegra_soc_desc;

struct arm_soc_smp_init_ops;
struct arm_soc_smp_ops;
extern struct arm_soc_smp_init_ops	tegra_soc_smp_init_ops;
extern struct arm_soc_smp_ops		tegra_soc_smp_ops;

extern int  tegra_cpu_kill(unsigned int cpu);
extern void tegra_cpu_die(unsigned int cpu);
extern int  tegra_cpu_disable(unsigned int cpu);