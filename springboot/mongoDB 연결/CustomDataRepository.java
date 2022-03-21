import java.time.LocalDate;
import java.util.Map;

public interface CustomDataRepository {

    public Map<Data, Integer> getDataCount(LocalDate st, LocalDate ed);
}
